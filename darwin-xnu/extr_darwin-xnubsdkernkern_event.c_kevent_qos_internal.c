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
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  kqueue_id_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 unsigned int KEVENT_FLAG_KERNEL ; 
 int kevent_internal (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned long long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
kevent_qos_internal(struct proc *p, int fd,
		    user_addr_t changelist, int nchanges,
		    user_addr_t eventlist, int nevents,
		    user_addr_t data_out, user_size_t *data_available,
		    unsigned int flags,
		    int32_t *retval)
{
	return kevent_internal(p,
	                       (kqueue_id_t)fd, NULL,
	                       changelist, nchanges,
	                       eventlist, nevents,
	                       data_out, (uint64_t)data_available,
	                       (flags | KEVENT_FLAG_KERNEL),
	                       0ULL,
	                       NULL,
	                       retval);
}