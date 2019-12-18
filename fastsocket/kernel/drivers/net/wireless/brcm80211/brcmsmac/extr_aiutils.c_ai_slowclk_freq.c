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
typedef  int uint ;
struct si_pub {int dummy; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPCREGOFFS (int /*<<< orphan*/ ) ; 
 int SYCC_CD_SHIFT ; 
 int XTALMAXFREQ ; 
 int XTALMINFREQ ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_clk_ctl ; 

__attribute__((used)) static uint ai_slowclk_freq(struct si_pub *sih, bool max_freq,
			    struct bcma_device *cc)
{
	uint div;

	/* Chipc rev 10 is InstaClock */
	div = bcma_read32(cc, CHIPCREGOFFS(system_clk_ctl));
	div = 4 * ((div >> SYCC_CD_SHIFT) + 1);
	return max_freq ? XTALMAXFREQ : (XTALMINFREQ / div);
}