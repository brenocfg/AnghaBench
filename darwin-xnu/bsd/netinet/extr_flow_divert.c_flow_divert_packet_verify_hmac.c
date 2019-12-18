#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct flow_divert_group {int /*<<< orphan*/  lck; int /*<<< orphan*/ * token_key; } ;
typedef  int /*<<< orphan*/  packet_hmac ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  FDLOG0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_HMAC ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  MBUF_WAITOK ; 
 int SHA_DIGEST_LENGTH ; 
 int flow_divert_packet_compute_hmac (int /*<<< orphan*/ ,struct flow_divert_group*,int /*<<< orphan*/ *) ; 
 int flow_divert_packet_find_tlv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int flow_divert_packet_get_tlv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_active_group_count ; 
 int /*<<< orphan*/  g_flow_divert_group_lck ; 
 struct flow_divert_group** g_flow_divert_groups ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_free (int /*<<< orphan*/ ) ; 
 int mbuf_split (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nil_pcb ; 

__attribute__((used)) static int
flow_divert_packet_verify_hmac(mbuf_t packet, uint32_t ctl_unit)
{
	int							error = 0;
	struct flow_divert_group	*group = NULL;
	int							hmac_offset;
	uint8_t						packet_hmac[SHA_DIGEST_LENGTH];
	uint8_t						computed_hmac[SHA_DIGEST_LENGTH];
	mbuf_t						tail;

	lck_rw_lock_shared(&g_flow_divert_group_lck);

	if (g_flow_divert_groups != NULL && g_active_group_count > 0) {
		group = g_flow_divert_groups[ctl_unit];
	}

	if (group == NULL) {
		lck_rw_done(&g_flow_divert_group_lck);
		return ENOPROTOOPT;
	}

	lck_rw_lock_shared(&group->lck);

	if (group->token_key == NULL) {
		error = ENOPROTOOPT;
		goto done;
	}

	hmac_offset = flow_divert_packet_find_tlv(packet, 0, FLOW_DIVERT_TLV_HMAC, &error, 0);
	if (hmac_offset < 0) {
		goto done;
	}

	error = flow_divert_packet_get_tlv(packet, hmac_offset, FLOW_DIVERT_TLV_HMAC, sizeof(packet_hmac), packet_hmac, NULL);
	if (error) {
		goto done;
	}

	/* Chop off the HMAC TLV */
	error = mbuf_split(packet, hmac_offset, MBUF_WAITOK, &tail);
	if (error) {
		goto done;
	}

	mbuf_free(tail);

	error = flow_divert_packet_compute_hmac(packet, group, computed_hmac);
	if (error) {
		goto done;
	}

	if (memcmp(packet_hmac, computed_hmac, sizeof(packet_hmac))) {
		FDLOG0(LOG_WARNING, &nil_pcb, "HMAC in token does not match computed HMAC");
		error = EINVAL;
		goto done;
	}

done:
	lck_rw_done(&group->lck);
	lck_rw_done(&g_flow_divert_group_lck);
	return error;
}