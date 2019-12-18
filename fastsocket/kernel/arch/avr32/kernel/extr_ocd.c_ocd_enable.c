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
typedef  int u32 ;
struct task_struct {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC ; 
 int OCD_DC_DBE_BIT ; 
 int OCD_DC_MM_BIT ; 
 int /*<<< orphan*/  TIF_DEBUG ; 
 int /*<<< orphan*/  ocd_count ; 
 int /*<<< orphan*/  ocd_lock ; 
 int ocd_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void ocd_enable(struct task_struct *child)
{
	u32 dc;

	if (child)
		pr_debug("ocd_enable: child=%s [%u]\n",
				child->comm, child->pid);
	else
		pr_debug("ocd_enable (no child)\n");

	if (!child || !test_and_set_tsk_thread_flag(child, TIF_DEBUG)) {
		spin_lock(&ocd_lock);
		ocd_count++;
		dc = ocd_read(DC);
		dc |= (1 << OCD_DC_MM_BIT) | (1 << OCD_DC_DBE_BIT);
		ocd_write(DC, dc);
		spin_unlock(&ocd_lock);
	}
}