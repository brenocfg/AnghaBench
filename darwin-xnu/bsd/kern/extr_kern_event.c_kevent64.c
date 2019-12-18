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
struct proc {int dummy; } ;
struct kevent64_args {unsigned int flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nevents; int /*<<< orphan*/  eventlist; int /*<<< orphan*/  nchanges; int /*<<< orphan*/  changelist; scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  kqueue_id_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 unsigned int KEVENT_FLAG_LEGACY64 ; 
 unsigned int KEVENT_FLAG_USER ; 
 int /*<<< orphan*/  kevent_continue ; 
 int kevent_internal (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kevent64(struct proc *p, struct kevent64_args *uap, int32_t *retval)
{
	unsigned int flags;

	/* restrict to user flags and set legacy64 */
	flags = uap->flags & KEVENT_FLAG_USER;
	flags |= KEVENT_FLAG_LEGACY64;

	return kevent_internal(p,
	                       (kqueue_id_t)uap->fd, NULL,
	                       uap->changelist, uap->nchanges,
	                       uap->eventlist, uap->nevents,
	                       0ULL, 0ULL,
	                       flags,
	                       uap->timeout,
	                       kevent_continue,
	                       retval);
}