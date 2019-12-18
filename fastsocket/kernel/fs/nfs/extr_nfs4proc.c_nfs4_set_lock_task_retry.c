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

/* Variables and functions */
 unsigned long NFS4_LOCK_MAXTIMEOUT ; 
 int /*<<< orphan*/  freezable_schedule_timeout_killable (unsigned long) ; 

__attribute__((used)) static unsigned long
nfs4_set_lock_task_retry(unsigned long timeout)
{
	freezable_schedule_timeout_killable(timeout);
	timeout <<= 1;
	if (timeout > NFS4_LOCK_MAXTIMEOUT)
		return NFS4_LOCK_MAXTIMEOUT;
	return timeout;
}