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
typedef  int u64 ;

/* Variables and functions */
 int MCI_CTL2_CMCI_EN ; 
 int MCI_CTL2_CMCI_THRESHOLD_MASK ; 
 int /*<<< orphan*/  MSR_IA32_MCx_CTL2 (int) ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmci_discover_lock ; 
 int /*<<< orphan*/  cmci_supported (int*) ; 
 int /*<<< orphan*/  mce_banks_owned ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

void cmci_clear(void)
{
	unsigned long flags;
	int i;
	int banks;
	u64 val;

	if (!cmci_supported(&banks))
		return;
	spin_lock_irqsave(&cmci_discover_lock, flags);
	for (i = 0; i < banks; i++) {
		if (!test_bit(i, __get_cpu_var(mce_banks_owned)))
			continue;
		/* Disable CMCI */
		rdmsrl(MSR_IA32_MCx_CTL2(i), val);
		val &= ~(MCI_CTL2_CMCI_EN|MCI_CTL2_CMCI_THRESHOLD_MASK);
		wrmsrl(MSR_IA32_MCx_CTL2(i), val);
		__clear_bit(i, __get_cpu_var(mce_banks_owned));
	}
	spin_unlock_irqrestore(&cmci_discover_lock, flags);
}