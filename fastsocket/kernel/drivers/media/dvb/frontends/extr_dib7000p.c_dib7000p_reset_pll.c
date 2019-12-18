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
typedef  int u16 ;
struct dibx000_bandwidth_config {int pll_ratio; int modulo; int ADClkSrc; int IO_CLK_en_core; int bypclk_div; int enable_refdiv; int pll_prediv; int pll_range; int pll_reset; int pll_bypass; int internal; int ifreq; int sad_cfg; } ;
struct TYPE_2__ {struct dibx000_bandwidth_config* bw; } ;
struct dib7000p_state {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 

__attribute__((used)) static void dib7000p_reset_pll(struct dib7000p_state *state)
{
	struct dibx000_bandwidth_config *bw = &state->cfg.bw[0];
	u16 clk_cfg0;

	/* force PLL bypass */
	clk_cfg0 = (1 << 15) | ((bw->pll_ratio & 0x3f) << 9) |
		(bw->modulo << 7) | (bw->ADClkSrc << 6) | (bw->IO_CLK_en_core << 5) |
		(bw->bypclk_div << 2) | (bw->enable_refdiv << 1) | (0 << 0);

	dib7000p_write_word(state, 900, clk_cfg0);

	/* P_pll_cfg */
	dib7000p_write_word(state, 903, (bw->pll_prediv << 5) | (((bw->pll_ratio >> 6) & 0x3) << 3) | (bw->pll_range << 1) | bw->pll_reset);
	clk_cfg0 = (bw->pll_bypass << 15) | (clk_cfg0 & 0x7fff);
	dib7000p_write_word(state, 900, clk_cfg0);

	dib7000p_write_word(state, 18, (u16) (((bw->internal*1000) >> 16) & 0xffff));
	dib7000p_write_word(state, 19, (u16) ( (bw->internal*1000       ) & 0xffff));
	dib7000p_write_word(state, 21, (u16) ( (bw->ifreq          >> 16) & 0xffff));
	dib7000p_write_word(state, 22, (u16) ( (bw->ifreq               ) & 0xffff));

	dib7000p_write_word(state, 72, bw->sad_cfg);
}