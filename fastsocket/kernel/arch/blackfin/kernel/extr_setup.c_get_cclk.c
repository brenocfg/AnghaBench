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
typedef  int u_long ;

/* Variables and functions */
 int bfin_read_PLL_DIV () ; 
 int bfin_read_PLL_STAT () ; 
 int get_clkin_hz () ; 
 int get_vco () ; 

u_long get_cclk(void)
{
	static u_long cached_cclk_pll_div, cached_cclk;
	u_long csel, ssel;

	if (bfin_read_PLL_STAT() & 0x1)
		return get_clkin_hz();

	ssel = bfin_read_PLL_DIV();
	if (ssel == cached_cclk_pll_div)
		return cached_cclk;
	else
		cached_cclk_pll_div = ssel;

	csel = ((ssel >> 4) & 0x03);
	ssel &= 0xf;
	if (ssel && ssel < (1 << csel))	/* SCLK > CCLK */
		cached_cclk = get_vco() / ssel;
	else
		cached_cclk = get_vco() >> csel;
	return cached_cclk;
}