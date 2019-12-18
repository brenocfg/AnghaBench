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
 int ENODEV ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap2_mcspi_restore_ctx (struct omap2_mcspi*) ; 

__attribute__((used)) static int omap2_mcspi_enable_clocks(struct omap2_mcspi *mcspi)
{
	if (clk_enable(mcspi->ick))
		return -ENODEV;
	if (clk_enable(mcspi->fck))
		return -ENODEV;

	omap2_mcspi_restore_ctx(mcspi);

	return 0;
}