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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE__READ ; 
 int /*<<< orphan*/  PROCESS__PTRACE ; 
 unsigned int PTRACE_MODE_READ ; 
 int /*<<< orphan*/  SECCLASS_FILE ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cap_ptrace_access_check (struct task_struct*,unsigned int) ; 
 int current_has_perm (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static int selinux_ptrace_access_check(struct task_struct *child,
				     unsigned int mode)
{
	int rc;

	rc = cap_ptrace_access_check(child, mode);
	if (rc)
		return rc;

	if (mode == PTRACE_MODE_READ) {
		u32 sid = current_sid();
		u32 csid = task_sid(child);
		return avc_has_perm(sid, csid, SECCLASS_FILE, FILE__READ, NULL);
	}

	return current_has_perm(child, PROCESS__PTRACE);
}