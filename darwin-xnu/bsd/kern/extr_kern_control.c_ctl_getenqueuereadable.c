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
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {scalar_t__ sb_cc; scalar_t__ sb_lowat; } ;
struct socket {TYPE_1__ so_rcv; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct socket* kcb_find_socket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

errno_t
ctl_getenqueuereadable(kern_ctl_ref kctlref, u_int32_t unit,
    u_int32_t *difference)
{
	struct socket 	*so;

	if (difference == NULL)
		return (EINVAL);

	so = kcb_find_socket(kctlref, unit, NULL);
	if (so == NULL) {
		return (EINVAL);
	}

	if (so->so_rcv.sb_cc >= so->so_rcv.sb_lowat) {
		*difference = 0;
	} else {
		*difference = (so->so_rcv.sb_lowat - so->so_rcv.sb_cc);
	}
	socket_unlock(so, 1);

	return (0);
}