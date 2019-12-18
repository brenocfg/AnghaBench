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
struct dlm_ls {int /*<<< orphan*/  ls_recoverd_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

void dlm_recoverd_stop(struct dlm_ls *ls)
{
	kthread_stop(ls->ls_recoverd_task);
}