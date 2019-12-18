#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sockopt {scalar_t__ sopt_val; int /*<<< orphan*/  sopt_valsize; } ;
struct socket {int so_flags; struct flow_divert_pcb* so_fd_pcb; } ;
struct flow_divert_pcb {int app_data_length; size_t control_group_unit; int /*<<< orphan*/ * app_data; int /*<<< orphan*/  hash; TYPE_1__* group; } ;
struct flow_divert_group {int /*<<< orphan*/  lck; int /*<<< orphan*/  ctl_unit; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  hmac ;
typedef  int errno_t ;
typedef  int /*<<< orphan*/  ctl_unit ;
struct TYPE_2__ {int /*<<< orphan*/  ctl_unit; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_APP_DATA ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_CTL_UNIT ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_FLOW_ID ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_HMAC ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_KEY_UNIT ; 
 size_t GROUP_COUNT_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 int /*<<< orphan*/  MBUF_TYPE_HEADER ; 
 int SHA_DIGEST_LENGTH ; 
 int SOF_FLOW_DIVERT ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int flow_divert_packet_append_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int flow_divert_packet_compute_hmac (int /*<<< orphan*/ *,struct flow_divert_group*,int /*<<< orphan*/ *) ; 
 scalar_t__ g_active_group_count ; 
 int /*<<< orphan*/  g_flow_divert_group_lck ; 
 struct flow_divert_group** g_flow_divert_groups ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ *) ; 
 int mbuf_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mbuf_pkthdr_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int soopt_mcopyout (struct sockopt*,int /*<<< orphan*/ *) ; 

errno_t
flow_divert_token_get(struct socket *so, struct sockopt *sopt)
{
	uint32_t					ctl_unit;
	int							error						= 0;
	uint8_t						hmac[SHA_DIGEST_LENGTH];
	struct flow_divert_pcb		*fd_cb						= so->so_fd_pcb;
	mbuf_t						token						= NULL;
	struct flow_divert_group	*control_group				= NULL;

	if (!(so->so_flags & SOF_FLOW_DIVERT)) {
		error = EINVAL;
		goto done;
	}

	VERIFY((so->so_flags & SOF_FLOW_DIVERT) && so->so_fd_pcb != NULL);

	if (fd_cb->group == NULL) {
		error = EINVAL;
		goto done;
	}

	error = mbuf_gethdr(MBUF_DONTWAIT, MBUF_TYPE_HEADER, &token);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to allocate the header mbuf: %d", error);
		goto done;
	}

	ctl_unit = htonl(fd_cb->group->ctl_unit);

	error = flow_divert_packet_append_tlv(token, FLOW_DIVERT_TLV_CTL_UNIT, sizeof(ctl_unit), &ctl_unit);
	if (error) {
		goto done;
	}

	error = flow_divert_packet_append_tlv(token, FLOW_DIVERT_TLV_FLOW_ID, sizeof(fd_cb->hash), &fd_cb->hash);
	if (error) {
		goto done;
	}

	if (fd_cb->app_data != NULL) {
		error = flow_divert_packet_append_tlv(token, FLOW_DIVERT_TLV_APP_DATA, fd_cb->app_data_length, fd_cb->app_data);
		if (error) {
			goto done;
		}
	}

	socket_unlock(so, 0);
	lck_rw_lock_shared(&g_flow_divert_group_lck);

	if (g_flow_divert_groups != NULL && g_active_group_count > 0 &&
	    fd_cb->control_group_unit > 0 && fd_cb->control_group_unit < GROUP_COUNT_MAX)
	{
		control_group = g_flow_divert_groups[fd_cb->control_group_unit];
	}

	if (control_group != NULL) {
		lck_rw_lock_shared(&control_group->lck);
		ctl_unit = htonl(control_group->ctl_unit);
		error = flow_divert_packet_append_tlv(token, FLOW_DIVERT_TLV_KEY_UNIT, sizeof(ctl_unit), &ctl_unit);
		if (!error) {
			error = flow_divert_packet_compute_hmac(token, control_group, hmac);
		}
		lck_rw_done(&control_group->lck);
	} else {
		error = ENOPROTOOPT;
	}

	lck_rw_done(&g_flow_divert_group_lck);
	socket_lock(so, 0);

	if (error) {
		goto done;
	}

	error = flow_divert_packet_append_tlv(token, FLOW_DIVERT_TLV_HMAC, sizeof(hmac), hmac);
	if (error) {
		goto done;
	}

	if (sopt->sopt_val == USER_ADDR_NULL) {
		/* If the caller passed NULL to getsockopt, just set the size of the token and return */
		sopt->sopt_valsize = mbuf_pkthdr_len(token);
		goto done;
	}

	error = soopt_mcopyout(sopt, token);
	if (error) {
		token = NULL;	/* For some reason, soopt_mcopyout() frees the mbuf if it fails */
		goto done;
	}

done:
	if (token != NULL) {
		mbuf_freem(token);
	}

	return error;
}