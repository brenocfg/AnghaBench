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
struct cred {int /*<<< orphan*/  cap_effective; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ cap_raised (int /*<<< orphan*/ ,int) ; 

int cap_capable(struct task_struct *tsk, const struct cred *cred, int cap,
		int audit)
{
	return cap_raised(cred->cap_effective, cap) ? 0 : -EPERM;
}