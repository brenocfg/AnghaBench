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
 int /*<<< orphan*/  SMSG_PREFIX ; 
 int /*<<< orphan*/  cmm_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmm_oom_nb ; 
 int /*<<< orphan*/  cmm_page_list ; 
 int /*<<< orphan*/  cmm_pages ; 
 int /*<<< orphan*/  cmm_power_notifier ; 
 int /*<<< orphan*/  cmm_smsg_target ; 
 int /*<<< orphan*/  cmm_sysctl_header ; 
 int /*<<< orphan*/  cmm_thread_ptr ; 
 int /*<<< orphan*/  cmm_timed_page_list ; 
 int /*<<< orphan*/  cmm_timed_pages ; 
 int /*<<< orphan*/  cmm_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsg_unregister_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_oom_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cmm_exit(void)
{
#ifdef CONFIG_CMM_PROC
	unregister_sysctl_table(cmm_sysctl_header);
#endif
#ifdef CONFIG_CMM_IUCV
	smsg_unregister_callback(SMSG_PREFIX, cmm_smsg_target);
#endif
	unregister_pm_notifier(&cmm_power_notifier);
	unregister_oom_notifier(&cmm_oom_nb);
	kthread_stop(cmm_thread_ptr);
	del_timer_sync(&cmm_timer);
	cmm_free_pages(cmm_pages, &cmm_pages, &cmm_page_list);
	cmm_free_pages(cmm_timed_pages, &cmm_timed_pages, &cmm_timed_page_list);
}