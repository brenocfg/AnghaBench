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
 char* DISPLAY_DIR_NAME ; 
 int PVC_NLINES ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pvc_display_dir ; 
 char** pvc_linename ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void pvc_proc_cleanup(void)
{
	int i;
	for (i = 0; i < PVC_NLINES; i++)
		remove_proc_entry(pvc_linename[i], pvc_display_dir);
	remove_proc_entry("scroll", pvc_display_dir);
	remove_proc_entry(DISPLAY_DIR_NAME, NULL);

	del_timer(&timer);
}