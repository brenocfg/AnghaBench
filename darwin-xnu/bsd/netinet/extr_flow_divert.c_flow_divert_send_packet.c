#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct flow_divert_pcb {TYPE_1__* group; TYPE_2__* so; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
struct TYPE_4__ {int so_error; } ;
struct TYPE_3__ {int /*<<< orphan*/  lck; int /*<<< orphan*/  atomic_bits; int /*<<< orphan*/  send_queue; int /*<<< orphan*/  ctl_unit; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 int ECONNABORTED ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GROUP_BIT_CTL_ENQUEUE_BLOCKED ; 
 scalar_t__ MBUFQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBUFQ_ENQUEUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSTestAndSet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ctl_enqueuembuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_divert_disconnect_socket (TYPE_2__*) ; 
 int /*<<< orphan*/  g_flow_divert_kctl_ref ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared_to_exclusive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flow_divert_send_packet(struct flow_divert_pcb *fd_cb, mbuf_t packet, Boolean enqueue)
{
	int		error;

	if (fd_cb->group == NULL) {
		fd_cb->so->so_error = ECONNABORTED;
		flow_divert_disconnect_socket(fd_cb->so);
		return ECONNABORTED;
	}

	lck_rw_lock_shared(&fd_cb->group->lck);

	if (MBUFQ_EMPTY(&fd_cb->group->send_queue)) {
		error = ctl_enqueuembuf(g_flow_divert_kctl_ref, fd_cb->group->ctl_unit, packet, CTL_DATA_EOR);
	} else {
		error = ENOBUFS;
	}

	if (error == ENOBUFS) {
		if (enqueue) {
			if (!lck_rw_lock_shared_to_exclusive(&fd_cb->group->lck)) {
				lck_rw_lock_exclusive(&fd_cb->group->lck);
			}
			MBUFQ_ENQUEUE(&fd_cb->group->send_queue, packet);
			error = 0;
		}
		OSTestAndSet(GROUP_BIT_CTL_ENQUEUE_BLOCKED, &fd_cb->group->atomic_bits);
	}

	lck_rw_done(&fd_cb->group->lck);

	return error;
}