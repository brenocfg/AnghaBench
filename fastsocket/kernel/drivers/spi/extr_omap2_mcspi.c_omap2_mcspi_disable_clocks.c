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
struct omap2_mcspi {int /*<<< orphan*/  fck; int /*<<< orphan*/  ick; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_mcspi_disable_clocks(struct omap2_mcspi *mcspi)
{
	clk_disable(mcspi->ick);
	clk_disable(mcspi->fck);
}