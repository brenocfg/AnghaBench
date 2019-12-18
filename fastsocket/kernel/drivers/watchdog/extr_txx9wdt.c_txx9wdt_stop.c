#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tcr; int /*<<< orphan*/  wtmr; } ;

/* Variables and functions */
 int TXx9_TMTCR_TCE ; 
 int TXx9_TMWTMR_WDIS ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9_lock ; 
 TYPE_1__* txx9wdt_reg ; 

__attribute__((used)) static void txx9wdt_stop(void)
{
	spin_lock(&txx9_lock);
	__raw_writel(TXx9_TMWTMR_WDIS, &txx9wdt_reg->wtmr);
	__raw_writel(__raw_readl(&txx9wdt_reg->tcr) & ~TXx9_TMTCR_TCE,
		     &txx9wdt_reg->tcr);
	spin_unlock(&txx9_lock);
}