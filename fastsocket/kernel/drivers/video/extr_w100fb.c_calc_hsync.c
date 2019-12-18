#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned long ss_end; unsigned long ss_start; } ;
union crtc_ss_u {TYPE_4__ f; scalar_t__ val; } ;
struct w100fb_par {unsigned long hsync_len; scalar_t__ fastpll_mode; TYPE_1__* mach; struct w100_mode* mode; } ;
struct w100_mode {scalar_t__ pixclk_src; int fast_pll_freq; int pll_freq; } ;
struct TYPE_7__ {int pclk_post_div; } ;
struct TYPE_8__ {TYPE_2__ f; } ;
struct TYPE_10__ {TYPE_3__ pclk_cntl; } ;
struct TYPE_6__ {unsigned long xtal_freq; } ;

/* Variables and functions */
 scalar_t__ CLK_SRC_XTAL ; 
 scalar_t__ mmCRTC_SS ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ remapped_regs ; 
 TYPE_5__ w100_pwr_state ; 

__attribute__((used)) static void calc_hsync(struct w100fb_par *par)
{
	unsigned long hsync;
	struct w100_mode *mode = par->mode;
	union crtc_ss_u crtc_ss;

	if (mode->pixclk_src == CLK_SRC_XTAL)
		hsync=par->mach->xtal_freq;
	else
		hsync=((par->fastpll_mode && mode->fast_pll_freq) ? mode->fast_pll_freq : mode->pll_freq)*100000;

	hsync /= (w100_pwr_state.pclk_cntl.f.pclk_post_div + 1);

	crtc_ss.val = readl(remapped_regs + mmCRTC_SS);
	if (crtc_ss.val)
		par->hsync_len = hsync / (crtc_ss.f.ss_end-crtc_ss.f.ss_start);
	else
		par->hsync_len = 0;
}