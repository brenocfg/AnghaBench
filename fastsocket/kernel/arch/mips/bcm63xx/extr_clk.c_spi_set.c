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
typedef  int /*<<< orphan*/  u32 ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCMCPU_IS_6338 () ; 
 scalar_t__ BCMCPU_IS_6348 () ; 
 int /*<<< orphan*/  CKCTL_6338_SPI_EN ; 
 int /*<<< orphan*/  CKCTL_6348_SPI_EN ; 
 int /*<<< orphan*/  CKCTL_6358_SPI_EN ; 
 int /*<<< orphan*/  bcm_hwclock_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void spi_set(struct clk *clk, int enable)
{
	u32 mask;

	if (BCMCPU_IS_6338())
		mask = CKCTL_6338_SPI_EN;
	else if (BCMCPU_IS_6348())
		mask = CKCTL_6348_SPI_EN;
	else
		/* BCMCPU_IS_6358 */
		mask = CKCTL_6358_SPI_EN;
	bcm_hwclock_set(mask, enable);
}