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
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSG_PREFIX ; 
 int /*<<< orphan*/ * cmm_default_sender ; 
 int /*<<< orphan*/  cmm_dir_table ; 
 int /*<<< orphan*/  cmm_oom_nb ; 
 int /*<<< orphan*/  cmm_power_notifier ; 
 int /*<<< orphan*/  cmm_smsg_target ; 
 int /*<<< orphan*/  cmm_sysctl_header ; 
 int /*<<< orphan*/  cmm_thread ; 
 int /*<<< orphan*/  cmm_thread_ptr ; 
 int /*<<< orphan*/  cmm_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int register_oom_notifier (int /*<<< orphan*/ *) ; 
 int register_pm_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sender ; 
 int smsg_register_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsg_unregister_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_oom_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmm_init (void)
{
	int rc = -ENOMEM;

#ifdef CONFIG_CMM_PROC
	cmm_sysctl_header = register_sysctl_table(cmm_dir_table);
	if (!cmm_sysctl_header)
		goto out_sysctl;
#endif
#ifdef CONFIG_CMM_IUCV
	/* convert sender to uppercase characters */
	if (sender) {
		int len = strlen(sender);
		while (len--)
			sender[len] = toupper(sender[len]);
	} else {
		sender = cmm_default_sender;
	}

	rc = smsg_register_callback(SMSG_PREFIX, cmm_smsg_target);
	if (rc < 0)
		goto out_smsg;
#endif
	rc = register_oom_notifier(&cmm_oom_nb);
	if (rc < 0)
		goto out_oom_notify;
	rc = register_pm_notifier(&cmm_power_notifier);
	if (rc)
		goto out_pm;
	cmm_thread_ptr = kthread_run(cmm_thread, NULL, "cmmthread");
	rc = IS_ERR(cmm_thread_ptr) ? PTR_ERR(cmm_thread_ptr) : 0;
	if (rc)
		goto out_kthread;
	return 0;

out_kthread:
	unregister_pm_notifier(&cmm_power_notifier);
out_pm:
	unregister_oom_notifier(&cmm_oom_nb);
out_oom_notify:
#ifdef CONFIG_CMM_IUCV
	smsg_unregister_callback(SMSG_PREFIX, cmm_smsg_target);
out_smsg:
#endif
#ifdef CONFIG_CMM_PROC
	unregister_sysctl_table(cmm_sysctl_header);
out_sysctl:
#endif
	del_timer_sync(&cmm_timer);
	return rc;
}