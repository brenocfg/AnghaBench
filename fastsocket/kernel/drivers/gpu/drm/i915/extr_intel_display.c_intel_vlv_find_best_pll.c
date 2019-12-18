#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_crtc {int dummy; } ;
struct TYPE_15__ {int min; int max; } ;
struct TYPE_14__ {int min; int max; } ;
struct TYPE_13__ {int p2_fast; } ;
struct TYPE_12__ {int max; int min; } ;
struct TYPE_11__ {int min; } ;
struct TYPE_16__ {TYPE_5__ vco; TYPE_4__ m1; TYPE_3__ p2; TYPE_2__ p1; TYPE_1__ n; } ;
typedef  TYPE_6__ intel_limit_t ;
struct TYPE_17__ {int n; int m1; int m2; int p1; int p2; } ;
typedef  TYPE_7__ intel_clock_t ;

/* Variables and functions */

__attribute__((used)) static bool
intel_vlv_find_best_pll(const intel_limit_t *limit, struct drm_crtc *crtc,
			int target, int refclk, intel_clock_t *match_clock,
			intel_clock_t *best_clock)
{
	u32 p1, p2, m1, m2, vco, bestn, bestm1, bestm2, bestp1, bestp2;
	u32 m, n, fastclk;
	u32 updrate, minupdate, fracbits, p;
	unsigned long bestppm, ppm, absppm;
	int dotclk, flag;

	flag = 0;
	dotclk = target * 1000;
	bestppm = 1000000;
	ppm = absppm = 0;
	fastclk = dotclk / (2*100);
	updrate = 0;
	minupdate = 19200;
	fracbits = 1;
	n = p = p1 = p2 = m = m1 = m2 = vco = bestn = 0;
	bestm1 = bestm2 = bestp1 = bestp2 = 0;

	/* based on hardware requirement, prefer smaller n to precision */
	for (n = limit->n.min; n <= ((refclk) / minupdate); n++) {
		updrate = refclk / n;
		for (p1 = limit->p1.max; p1 > limit->p1.min; p1--) {
			for (p2 = limit->p2.p2_fast+1; p2 > 0; p2--) {
				if (p2 > 10)
					p2 = p2 - 1;
				p = p1 * p2;
				/* based on hardware requirement, prefer bigger m1,m2 values */
				for (m1 = limit->m1.min; m1 <= limit->m1.max; m1++) {
					m2 = (((2*(fastclk * p * n / m1 )) +
					       refclk) / (2*refclk));
					m = m1 * m2;
					vco = updrate * m;
					if (vco >= limit->vco.min && vco < limit->vco.max) {
						ppm = 1000000 * ((vco / p) - fastclk) / fastclk;
						absppm = (ppm > 0) ? ppm : (-ppm);
						if (absppm < 100 && ((p1 * p2) > (bestp1 * bestp2))) {
							bestppm = 0;
							flag = 1;
						}
						if (absppm < bestppm - 10) {
							bestppm = absppm;
							flag = 1;
						}
						if (flag) {
							bestn = n;
							bestm1 = m1;
							bestm2 = m2;
							bestp1 = p1;
							bestp2 = p2;
							flag = 0;
						}
					}
				}
			}
		}
	}
	best_clock->n = bestn;
	best_clock->m1 = bestm1;
	best_clock->m2 = bestm2;
	best_clock->p1 = bestp1;
	best_clock->p2 = bestp2;

	return true;
}