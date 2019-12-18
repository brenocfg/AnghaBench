#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int min_freq; int max_freq; int min_m; int max_m; int min_n; int max_n; int min_inputfreq; int max_inputfreq; } ;
struct nvbios_pll {int min_p; int max_p_usable; int refclk; TYPE_2__ vco1; } ;
struct nouveau_clock {int dummy; } ;
struct TYPE_4__ {int chip; } ;
struct TYPE_6__ {TYPE_1__ version; } ;

/* Variables and functions */
 int INT_MAX ; 
 int abs (int) ; 
 TYPE_3__* nouveau_bios (struct nouveau_clock*) ; 

__attribute__((used)) static int
getMNP_single(struct nouveau_clock *clock, struct nvbios_pll *info, int clk,
	      int *pN, int *pM, int *pP)
{
	/* Find M, N and P for a single stage PLL
	 *
	 * Note that some bioses (NV3x) have lookup tables of precomputed MNP
	 * values, but we're too lazy to use those atm
	 *
	 * "clk" parameter in kHz
	 * returns calculated clock
	 */
	int cv = nouveau_bios(clock)->version.chip;
	int minvco = info->vco1.min_freq, maxvco = info->vco1.max_freq;
	int minM = info->vco1.min_m, maxM = info->vco1.max_m;
	int minN = info->vco1.min_n, maxN = info->vco1.max_n;
	int minU = info->vco1.min_inputfreq;
	int maxU = info->vco1.max_inputfreq;
	int minP = info->min_p;
	int maxP = info->max_p_usable;
	int crystal = info->refclk;
	int M, N, thisP, P;
	int clkP, calcclk;
	int delta, bestdelta = INT_MAX;
	int bestclk = 0;

	/* this division verified for nv20, nv18, nv28 (Haiku), and nv34 */
	/* possibly correlated with introduction of 27MHz crystal */
	if (cv < 0x17 || cv == 0x1a || cv == 0x20) {
		if (clk > 250000)
			maxM = 6;
		if (clk > 340000)
			maxM = 2;
	} else if (cv < 0x40) {
		if (clk > 150000)
			maxM = 6;
		if (clk > 200000)
			maxM = 4;
		if (clk > 340000)
			maxM = 2;
	}

	P = 1 << maxP;
	if ((clk * P) < minvco) {
		minvco = clk * maxP;
		maxvco = minvco * 2;
	}

	if (clk + clk/200 > maxvco)	/* +0.5% */
		maxvco = clk + clk/200;

	/* NV34 goes maxlog2P->0, NV20 goes 0->maxlog2P */
	for (thisP = minP; thisP <= maxP; thisP++) {
		P = 1 << thisP;
		clkP = clk * P;

		if (clkP < minvco)
			continue;
		if (clkP > maxvco)
			return bestclk;

		for (M = minM; M <= maxM; M++) {
			if (crystal/M < minU)
				return bestclk;
			if (crystal/M > maxU)
				continue;

			/* add crystal/2 to round better */
			N = (clkP * M + crystal/2) / crystal;

			if (N < minN)
				continue;
			if (N > maxN)
				break;

			/* more rounding additions */
			calcclk = ((N * crystal + P/2) / P + M/2) / M;
			delta = abs(calcclk - clk);
			/* we do an exhaustive search rather than terminating
			 * on an optimality condition...
			 */
			if (delta < bestdelta) {
				bestdelta = delta;
				bestclk = calcclk;
				*pN = N;
				*pM = M;
				*pP = thisP;
				if (delta == 0)	/* except this one */
					return bestclk;
			}
		}
	}

	return bestclk;
}