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
struct psif {int /*<<< orphan*/  pclk; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PSIF_PSR_PRSCV_SIZE ; 
 int /*<<< orphan*/  PSR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  psif_writel (struct psif*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void psif_set_prescaler(struct psif *psif)
{
	unsigned long prscv;
	unsigned long rate = clk_get_rate(psif->pclk);

	/* PRSCV = Pulse length (100 us) * PSIF module frequency. */
	prscv = 100 * (rate / 1000000UL);

	if (prscv > ((1<<PSIF_PSR_PRSCV_SIZE) - 1)) {
		prscv = (1<<PSIF_PSR_PRSCV_SIZE) - 1;
		dev_dbg(&psif->pdev->dev, "pclk too fast, "
				"prescaler set to max\n");
	}

	clk_enable(psif->pclk);
	psif_writel(psif, PSR, prscv);
	clk_disable(psif->pclk);
}