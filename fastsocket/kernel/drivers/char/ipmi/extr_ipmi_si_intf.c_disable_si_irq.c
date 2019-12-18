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
struct smi_info {int interrupt_disabled; int /*<<< orphan*/  si_timer; int /*<<< orphan*/  stop_operation; scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ SI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  start_disable_irq (struct smi_info*) ; 

__attribute__((used)) static inline void disable_si_irq(struct smi_info *smi_info)
{
	if ((smi_info->irq) && (!smi_info->interrupt_disabled)) {
		start_disable_irq(smi_info);
		smi_info->interrupt_disabled = 1;
		if (!atomic_read(&smi_info->stop_operation))
			mod_timer(&smi_info->si_timer, jiffies + SI_TIMEOUT_JIFFIES);
	}
}