#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct clk {unsigned long rate; } ;
struct TYPE_12__ {int* pccr; } ;
struct TYPE_11__ {unsigned long rate; } ;
struct TYPE_10__ {unsigned long rate; } ;
struct TYPE_9__ {unsigned long rate; } ;
struct TYPE_8__ {unsigned long rate; } ;
struct TYPE_7__ {unsigned long rate; } ;

/* Variables and functions */
 TYPE_6__* clockctl ; 
 int /*<<< orphan*/  out_be32 (int*,int) ; 
 TYPE_5__ psc_mclk_in ; 
 TYPE_4__ ref_clk ; 
 TYPE_3__ spdif_rxclk ; 
 TYPE_2__ spdif_txclk ; 
 TYPE_1__ sys_clk ; 

__attribute__((used)) static void psc_calc_rate(struct clk *clk, int pscnum, struct device_node *np)
{
	unsigned long mclk_src = sys_clk.rate;
	unsigned long mclk_div;

	/*
	 * Can only change value of mclk divider
	 * when the divider is disabled.
	 *
	 * Zero is not a valid divider so minimum
	 * divider is 1
	 *
	 * disable/set divider/enable
	 */
	out_be32(&clockctl->pccr[pscnum], 0);
	out_be32(&clockctl->pccr[pscnum], 0x00020000);
	out_be32(&clockctl->pccr[pscnum], 0x00030000);

	if (clockctl->pccr[pscnum] & 0x80) {
		clk->rate = spdif_rxclk.rate;
		return;
	}

	switch ((clockctl->pccr[pscnum] >> 14) & 0x3) {
	case 0:
		mclk_src = sys_clk.rate;
		break;
	case 1:
		mclk_src = ref_clk.rate;
		break;
	case 2:
		mclk_src = psc_mclk_in.rate;
		break;
	case 3:
		mclk_src = spdif_txclk.rate;
		break;
	}

	mclk_div = ((clockctl->pccr[pscnum] >> 17) & 0x7fff) + 1;
	clk->rate = mclk_src / mclk_div;
}