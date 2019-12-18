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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int get_sclk () ; 

__attribute__((used)) static inline u16 get_eppi_clkdiv(u32 target_ppi_clk)
{
	u32 sclk = get_sclk();

	/* EPPI_CLK = (SCLK) / (2 * (EPPI_CLKDIV[15:0] + 1)) */

	return (((sclk / target_ppi_clk) / 2) - 1);
}