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
typedef  scalar_t__ u32 ;
struct task_struct {int dummy; } ;
struct siginfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ PROCESS__SIGNULL ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int current_has_perm (struct task_struct*,scalar_t__) ; 
 scalar_t__ signal_to_av (int) ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static int selinux_task_kill(struct task_struct *p, struct siginfo *info,
				int sig, u32 secid)
{
	u32 perm;
	int rc;

	if (!sig)
		perm = PROCESS__SIGNULL; /* null signal; existence test */
	else
		perm = signal_to_av(sig);
	if (secid)
		rc = avc_has_perm(secid, task_sid(p),
				  SECCLASS_PROCESS, perm, NULL);
	else
		rc = current_has_perm(p, perm);
	return rc;
}