#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {scalar_t__ sb_cc; int /*<<< orphan*/  sb_mb; } ;
struct socket {TYPE_1__ so_rcv; struct flow_divert_pcb* so_fd_pcb; void* so_proto; int /*<<< orphan*/  so_flags; } ;
struct inpcb {struct ifnet* inp_last_outifp; } ;
struct ifnet {int dummy; } ;
struct flow_divert_pcb {int /*<<< orphan*/  flags; struct socket* so; } ;
struct flow_divert_group {int dummy; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int errno_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FDLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  FDRELEASE (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDUNLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FLOW_DIVERT_TRANSFERRED ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_DOM (struct socket*) ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (struct socket*) ; 
 int /*<<< orphan*/  SOF_FLOW_DIVERT ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_divert_disconnect_socket (struct socket*) ; 
 struct flow_divert_pcb* flow_divert_pcb_lookup (size_t,struct flow_divert_group*) ; 
 int /*<<< orphan*/  flow_divert_set_protosw (struct socket*) ; 
 scalar_t__ g_active_group_count ; 
 int /*<<< orphan*/  g_flow_divert_group_lck ; 
 struct flow_divert_group** g_flow_divert_groups ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int mbuf_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nil_pcb ; 
 void* pffindproto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sbappendstream (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbflush (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static errno_t
flow_divert_attach(struct socket *so, uint32_t flow_id, uint32_t ctl_unit)
{
	int									error		= 0;
	struct flow_divert_pcb				*fd_cb		= NULL;
	struct ifnet						*ifp		= NULL;
	struct inpcb						*inp		= NULL;
	struct socket						*old_so;
	mbuf_t								recv_data	= NULL;

	socket_unlock(so, 0);

	FDLOG(LOG_INFO, &nil_pcb, "Attaching socket to flow %u", flow_id);

	/* Find the flow divert control block */
	lck_rw_lock_shared(&g_flow_divert_group_lck);
	if (g_flow_divert_groups != NULL && g_active_group_count > 0) {
		struct flow_divert_group *group = g_flow_divert_groups[ctl_unit];
		if (group != NULL) {
			fd_cb = flow_divert_pcb_lookup(flow_id, group);
		}
	}
	lck_rw_done(&g_flow_divert_group_lck);

	if (fd_cb == NULL) {
		error = ENOENT;
		goto done;
	}

	FDLOCK(fd_cb);

	/* Dis-associate the flow divert control block from its current socket */
	old_so = fd_cb->so;

	inp = sotoinpcb(old_so); 

	VERIFY(inp != NULL);

	socket_lock(old_so, 0);
	flow_divert_disconnect_socket(old_so);
	old_so->so_flags &= ~SOF_FLOW_DIVERT;
	old_so->so_fd_pcb = NULL;
	if (SOCK_TYPE(old_so) == SOCK_STREAM) {
		old_so->so_proto = pffindproto(SOCK_DOM(old_so), IPPROTO_TCP, SOCK_STREAM);
	} else if (SOCK_TYPE(old_so) == SOCK_DGRAM) {
		old_so->so_proto = pffindproto(SOCK_DOM(old_so), IPPROTO_UDP, SOCK_DGRAM);
	}
	fd_cb->so = NULL;
	/* Save the output interface */
	ifp = inp->inp_last_outifp;
	if (old_so->so_rcv.sb_cc > 0) {
		error = mbuf_dup(old_so->so_rcv.sb_mb, MBUF_DONTWAIT, &recv_data);
		sbflush(&old_so->so_rcv);
	}
	socket_unlock(old_so, 0);

	/* Associate the new socket with the flow divert control block */
	socket_lock(so, 0);
	so->so_fd_pcb = fd_cb;
	inp = sotoinpcb(so);
	inp->inp_last_outifp = ifp;
	if (recv_data != NULL) {
		if (sbappendstream(&so->so_rcv, recv_data)) {
			sorwakeup(so);
		}
	}
	flow_divert_set_protosw(so);
	socket_unlock(so, 0);

	fd_cb->so = so;
	fd_cb->flags |= FLOW_DIVERT_TRANSFERRED;

	FDUNLOCK(fd_cb);

done:
	socket_lock(so, 0);

	if (fd_cb != NULL) {
		FDRELEASE(fd_cb);	/* Release the reference obtained via flow_divert_pcb_lookup */
	}

	return error;
}