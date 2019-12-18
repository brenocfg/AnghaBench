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
 unsigned long KS8695_CLOCK_RATE ; 
 scalar_t__ KS8695_T0TC ; 
 scalar_t__ KS8695_TMCON ; 
 scalar_t__ KS8695_TMR_VA ; 
 unsigned long T0TC_WATCHDOG ; 
 unsigned long TMCON_T0EN ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  ks8695_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long wdt_time ; 

__attribute__((used)) static inline void ks8695_wdt_start(void)
{
	unsigned long tmcon;
	unsigned long tval = wdt_time * KS8695_CLOCK_RATE;

	spin_lock(&ks8695_lock);
	/* disable timer0 */
	tmcon = __raw_readl(KS8695_TMR_VA + KS8695_TMCON);
	__raw_writel(tmcon & ~TMCON_T0EN, KS8695_TMR_VA + KS8695_TMCON);

	/* program timer0 */
	__raw_writel(tval | T0TC_WATCHDOG, KS8695_TMR_VA + KS8695_T0TC);

	/* re-enable timer0 */
	tmcon = __raw_readl(KS8695_TMR_VA + KS8695_TMCON);
	__raw_writel(tmcon | TMCON_T0EN, KS8695_TMR_VA + KS8695_TMCON);
	spin_unlock(&ks8695_lock);
}