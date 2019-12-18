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
struct smi_info {size_t intf_num; scalar_t__ si_type; int /*<<< orphan*/ * thread; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  si_timer; scalar_t__ last_timeout_jiffies; int /*<<< orphan*/  (* irq_setup ) (struct smi_info*) ;int /*<<< orphan*/  intf; } ;
typedef  int /*<<< orphan*/  ipmi_smi_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SI_BT ; 
 scalar_t__ SI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int* force_kipmid ; 
 int /*<<< orphan*/  ipmi_thread ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct smi_info*,char*,size_t) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 size_t num_force_kipmid ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  smi_timeout ; 
 int /*<<< orphan*/  stub1 (struct smi_info*) ; 

__attribute__((used)) static int smi_start_processing(void       *send_info,
				ipmi_smi_t intf)
{
	struct smi_info *new_smi = send_info;
	int             enable = 0;

	new_smi->intf = intf;

	/* Try to claim any interrupts. */
	if (new_smi->irq_setup)
		new_smi->irq_setup(new_smi);

	/* Set up the timer that drives the interface. */
	setup_timer(&new_smi->si_timer, smi_timeout, (long)new_smi);
	new_smi->last_timeout_jiffies = jiffies;
	mod_timer(&new_smi->si_timer, jiffies + SI_TIMEOUT_JIFFIES);

	/*
	 * Check if the user forcefully enabled the daemon.
	 */
	if (new_smi->intf_num < num_force_kipmid)
		enable = force_kipmid[new_smi->intf_num];
	/*
	 * The BT interface is efficient enough to not need a thread,
	 * and there is no need for a thread if we have interrupts.
	 */
	else if ((new_smi->si_type != SI_BT) && (!new_smi->irq))
		enable = 1;

	if (enable) {
		new_smi->thread = kthread_run(ipmi_thread, new_smi,
					      "kipmi%d", new_smi->intf_num);
		if (IS_ERR(new_smi->thread)) {
			dev_notice(new_smi->dev, "Could not start"
				   " kernel thread due to error %ld, only using"
				   " timers to drive the interface\n",
				   PTR_ERR(new_smi->thread));
			new_smi->thread = NULL;
		}
	}

	return 0;
}