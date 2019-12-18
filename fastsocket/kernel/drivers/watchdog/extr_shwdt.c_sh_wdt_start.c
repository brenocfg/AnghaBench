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
typedef  int __u8 ;

/* Variables and functions */
 int HZ ; 
 int RSTCSR_RSTS ; 
 int WTCSR_RSTS ; 
 int WTCSR_TME ; 
 int WTCSR_WT ; 
 int clock_division_ratio ; 
 int heartbeat ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ next_heartbeat ; 
 int /*<<< orphan*/  next_ping_period (int) ; 
 int sh_wdt_read_csr () ; 
 int sh_wdt_read_rstcsr () ; 
 int /*<<< orphan*/  sh_wdt_write_cnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_wdt_write_csr (int) ; 
 int /*<<< orphan*/  sh_wdt_write_rstcsr (int) ; 
 int /*<<< orphan*/  shwdt_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void sh_wdt_start(void)
{
	__u8 csr;
	unsigned long flags;

	spin_lock_irqsave(&shwdt_lock, flags);

	next_heartbeat = jiffies + (heartbeat * HZ);
	mod_timer(&timer, next_ping_period(clock_division_ratio));

	csr = sh_wdt_read_csr();
	csr |= WTCSR_WT | clock_division_ratio;
	sh_wdt_write_csr(csr);

	sh_wdt_write_cnt(0);

	/*
	 * These processors have a bit of an inconsistent initialization
	 * process.. starting with SH-3, RSTS was moved to WTCSR, and the
	 * RSTCSR register was removed.
	 *
	 * On the SH-2 however, in addition with bits being in different
	 * locations, we must deal with RSTCSR outright..
	 */
	csr = sh_wdt_read_csr();
	csr |= WTCSR_TME;
	csr &= ~WTCSR_RSTS;
	sh_wdt_write_csr(csr);

#ifdef CONFIG_CPU_SH2
	/*
	 * Whoever came up with the RSTCSR semantics must've been smoking
	 * some of the good stuff, since in addition to the WTCSR/WTCNT write
	 * brain-damage, it's managed to fuck things up one step further..
	 *
	 * If we need to clear the WOVF bit, the upper byte has to be 0xa5..
	 * but if we want to touch RSTE or RSTS, the upper byte has to be
	 * 0x5a..
	 */
	csr = sh_wdt_read_rstcsr();
	csr &= ~RSTCSR_RSTS;
	sh_wdt_write_rstcsr(csr);
#endif
	spin_unlock_irqrestore(&shwdt_lock, flags);
}