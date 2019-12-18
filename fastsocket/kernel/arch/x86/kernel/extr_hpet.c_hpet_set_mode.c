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
typedef  int uint64_t ;
struct hpet_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  cpu; } ;
struct clock_event_device {int mult; int shift; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 struct hpet_dev* EVT_TO_HPET_DEV (struct clock_event_device*) ; 
 int /*<<< orphan*/  HPET_COUNTER ; 
 unsigned long HPET_TN_32BIT ; 
 unsigned long HPET_TN_ENABLE ; 
 unsigned long HPET_TN_LEVEL ; 
 unsigned long HPET_TN_PERIODIC ; 
 unsigned long HPET_TN_SETVAL ; 
 int /*<<< orphan*/  HPET_Tn_CFG (int) ; 
 int /*<<< orphan*/  HPET_Tn_CMP (int) ; 
 int HZ ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_enable_legacy_int () ; 
 int /*<<< orphan*/  hpet_print_config () ; 
 unsigned long hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_setup_msi_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_start_counter () ; 
 int /*<<< orphan*/  hpet_stop_counter () ; 
 int /*<<< orphan*/  hpet_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hpet_set_mode(enum clock_event_mode mode,
			  struct clock_event_device *evt, int timer)
{
	unsigned long cfg, cmp, now;
	uint64_t delta;

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		hpet_stop_counter();
		delta = ((uint64_t)(NSEC_PER_SEC/HZ)) * evt->mult;
		delta >>= evt->shift;
		now = hpet_readl(HPET_COUNTER);
		cmp = now + (unsigned long) delta;
		cfg = hpet_readl(HPET_Tn_CFG(timer));
		/* Make sure we use edge triggered interrupts */
		cfg &= ~HPET_TN_LEVEL;
		cfg |= HPET_TN_ENABLE | HPET_TN_PERIODIC |
		       HPET_TN_SETVAL | HPET_TN_32BIT;
		hpet_writel(cfg, HPET_Tn_CFG(timer));
		hpet_writel(cmp, HPET_Tn_CMP(timer));
		udelay(1);
		/*
		 * HPET on AMD 81xx needs a second write (with HPET_TN_SETVAL
		 * cleared) to T0_CMP to set the period. The HPET_TN_SETVAL
		 * bit is automatically cleared after the first write.
		 * (See AMD-8111 HyperTransport I/O Hub Data Sheet,
		 * Publication # 24674)
		 */
		hpet_writel((unsigned long) delta, HPET_Tn_CMP(timer));
		hpet_start_counter();
		hpet_print_config();
		break;

	case CLOCK_EVT_MODE_ONESHOT:
		cfg = hpet_readl(HPET_Tn_CFG(timer));
		cfg &= ~HPET_TN_PERIODIC;
		cfg |= HPET_TN_ENABLE | HPET_TN_32BIT;
		hpet_writel(cfg, HPET_Tn_CFG(timer));
		break;

	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		cfg = hpet_readl(HPET_Tn_CFG(timer));
		cfg &= ~HPET_TN_ENABLE;
		hpet_writel(cfg, HPET_Tn_CFG(timer));
		break;

	case CLOCK_EVT_MODE_RESUME:
		if (timer == 0) {
			hpet_enable_legacy_int();
		} else {
			struct hpet_dev *hdev = EVT_TO_HPET_DEV(evt);
			hpet_setup_msi_irq(hdev->irq);
			disable_irq(hdev->irq);
			irq_set_affinity(hdev->irq, cpumask_of(hdev->cpu));
			enable_irq(hdev->irq);
		}
		hpet_print_config();
		break;
	}
}