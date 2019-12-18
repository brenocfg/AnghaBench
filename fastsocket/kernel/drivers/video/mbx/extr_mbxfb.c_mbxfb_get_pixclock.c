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
typedef  int u8 ;
struct pixclock_div {int m; int n; int p; } ;

/* Variables and functions */
 unsigned int KHZ2PICOS (unsigned int) ; 
 unsigned int PICOS2KHZ (unsigned int) ; 

__attribute__((used)) static unsigned int mbxfb_get_pixclock(unsigned int pixclock_ps,
				       struct pixclock_div *div)
{
	u8 m, n, p;
	unsigned int err = 0;
	unsigned int min_err = ~0x0;
	unsigned int clk;
	unsigned int best_clk = 0;
	unsigned int ref_clk = 13000;	/* FIXME: take from platform data */
	unsigned int pixclock;

	/* convert pixclock to KHz */
	pixclock = PICOS2KHZ(pixclock_ps);

	/* PLL output freq = (ref_clk * M) / (N * 2^P)
	 *
	 * M: 1 to 63
	 * N: 1 to 7
	 * P: 0 to 7
	 */

	/* RAPH: When N==1, the resulting pixel clock appears to
	 * get divided by 2. Preventing N=1 by starting the following
	 * loop at 2 prevents this. Is this a bug with my chip
	 * revision or something I dont understand? */
	for (m = 1; m < 64; m++) {
		for (n = 2; n < 8; n++) {
			for (p = 0; p < 8; p++) {
				clk = (ref_clk * m) / (n * (1 << p));
				err = (clk > pixclock) ? (clk - pixclock) :
					(pixclock - clk);
				if (err < min_err) {
					min_err = err;
					best_clk = clk;
					div->m = m;
					div->n = n;
					div->p = p;
				}
			}
		}
	}
	return KHZ2PICOS(best_clk);
}