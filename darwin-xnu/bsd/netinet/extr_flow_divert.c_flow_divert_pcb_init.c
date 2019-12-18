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
typedef  int /*<<< orphan*/  uint32_t ;
struct socket {int so_flags; struct flow_divert_pcb* so_fd_pcb; } ;
struct flow_divert_pcb {int /*<<< orphan*/  control_group_unit; } ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EALREADY ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,scalar_t__) ; 
 int /*<<< orphan*/  FDLOG0 (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*) ; 
 int /*<<< orphan*/  FDRELEASE (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (struct socket*) ; 
 int SOF_FLOW_DIVERT ; 
 struct flow_divert_pcb* flow_divert_pcb_create (struct socket*) ; 
 scalar_t__ flow_divert_pcb_insert (struct flow_divert_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_divert_set_protosw (struct socket*) ; 
 int /*<<< orphan*/  flow_divert_set_udp_protosw (struct socket*) ; 

errno_t
flow_divert_pcb_init(struct socket *so, uint32_t ctl_unit)
{
	errno_t error = 0;
	struct flow_divert_pcb *fd_cb;

	if (so->so_flags & SOF_FLOW_DIVERT) {
		return EALREADY;
	}
		
	fd_cb = flow_divert_pcb_create(so);
	if (fd_cb != NULL) {
		error = flow_divert_pcb_insert(fd_cb, ctl_unit);
		if (error) {
			FDLOG(LOG_ERR, fd_cb, "pcb insert failed: %d", error);
			FDRELEASE(fd_cb);
		} else {
			fd_cb->control_group_unit = ctl_unit;
			so->so_fd_pcb = fd_cb;

			if (SOCK_TYPE(so) == SOCK_STREAM) {
				flow_divert_set_protosw(so);
			} else if (SOCK_TYPE(so) == SOCK_DGRAM) {
				flow_divert_set_udp_protosw(so);
			}

			FDLOG0(LOG_INFO, fd_cb, "Created");
		}
	} else {
		error = ENOMEM;
	}

	return error;
}