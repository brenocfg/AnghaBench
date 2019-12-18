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
struct nv_sim_state {int pclk_khz; int mclk_khz; int nvclk_khz; int mem_page_miss; int mem_latency; int memory_width; int bpp; } ;
struct nv_fifo_info {int lwm; int burst; } ;

/* Variables and functions */

__attribute__((used)) static void
nv04_calc_arb(struct nv_fifo_info *fifo, struct nv_sim_state *arb)
{
	int pagemiss, cas, width, bpp;
	int nvclks, mclks, pclks, crtpagemiss;
	int found, mclk_extra, mclk_loop, cbs, m1, p1;
	int mclk_freq, pclk_freq, nvclk_freq;
	int us_m, us_n, us_p, crtc_drain_rate;
	int cpm_us, us_crt, clwm;

	pclk_freq = arb->pclk_khz;
	mclk_freq = arb->mclk_khz;
	nvclk_freq = arb->nvclk_khz;
	pagemiss = arb->mem_page_miss;
	cas = arb->mem_latency;
	width = arb->memory_width >> 6;
	bpp = arb->bpp;
	cbs = 128;

	pclks = 2;
	nvclks = 10;
	mclks = 13 + cas;
	mclk_extra = 3;
	found = 0;

	while (!found) {
		found = 1;

		mclk_loop = mclks + mclk_extra;
		us_m = mclk_loop * 1000 * 1000 / mclk_freq;
		us_n = nvclks * 1000 * 1000 / nvclk_freq;
		us_p = nvclks * 1000 * 1000 / pclk_freq;

		crtc_drain_rate = pclk_freq * bpp / 8;
		crtpagemiss = 2;
		crtpagemiss += 1;
		cpm_us = crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
		us_crt = cpm_us + us_m + us_n + us_p;
		clwm = us_crt * crtc_drain_rate / (1000 * 1000);
		clwm++;

		m1 = clwm + cbs - 512;
		p1 = m1 * pclk_freq / mclk_freq;
		p1 = p1 * bpp / 8;
		if ((p1 < m1 && m1 > 0) || clwm > 519) {
			found = !mclk_extra;
			mclk_extra--;
		}
		if (clwm < 384)
			clwm = 384;

		fifo->lwm = clwm;
		fifo->burst = cbs;
	}
}