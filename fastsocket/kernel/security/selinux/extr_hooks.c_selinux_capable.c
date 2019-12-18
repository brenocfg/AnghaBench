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
struct task_struct {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int cap_capable (struct task_struct*,struct cred const*,int,int) ; 
 int task_has_capability (struct task_struct*,struct cred const*,int,int) ; 

__attribute__((used)) static int selinux_capable(struct task_struct *tsk, const struct cred *cred,
			   int cap, int audit)
{
	int rc;

	rc = cap_capable(tsk, cred, cap, audit);
	if (rc)
		return rc;

	return task_has_capability(tsk, cred, cap, audit);
}