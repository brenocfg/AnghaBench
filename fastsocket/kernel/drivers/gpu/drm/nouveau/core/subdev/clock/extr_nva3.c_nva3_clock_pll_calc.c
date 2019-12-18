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
struct nvbios_pll {int /*<<< orphan*/  refclk; } ;
struct nouveau_pll_vals {int N1; int M1; int log2P; int /*<<< orphan*/  refclk; } ;
struct nouveau_clock {int dummy; } ;

/* Variables and functions */
 int nva3_pll_calc (struct nouveau_clock*,struct nvbios_pll*,int,int*,int /*<<< orphan*/ *,int*,int*) ; 

int
nva3_clock_pll_calc(struct nouveau_clock *clock, struct nvbios_pll *info,
		    int clk, struct nouveau_pll_vals *pv)
{
	int ret, N, M, P;

	ret = nva3_pll_calc(clock, info, clk, &N, NULL, &M, &P);

	if (ret > 0) {
		pv->refclk = info->refclk;
		pv->N1 = N;
		pv->M1 = M;
		pv->log2P = P;
	}
	return ret;
}