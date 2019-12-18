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

/* Variables and functions */
 int /*<<< orphan*/  MAY_READ ; 
 int smk_curacc_on_task (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_task_getscheduler(struct task_struct *p)
{
	return smk_curacc_on_task(p, MAY_READ);
}