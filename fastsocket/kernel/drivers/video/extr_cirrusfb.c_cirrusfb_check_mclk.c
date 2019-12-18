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
struct fb_info {int /*<<< orphan*/  device; struct cirrusfb_info* par; } ;
struct cirrusfb_info {int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_SEQR1F ; 
 int abs (long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int vga_rseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cirrusfb_check_mclk(struct fb_info *info, long freq)
{
	struct cirrusfb_info *cinfo = info->par;
	long mclk = vga_rseq(cinfo->regbase, CL_SEQR1F) & 0x3f;

	/* Read MCLK value */
	mclk = (14318 * mclk) >> 3;
	dev_dbg(info->device, "Read MCLK of %ld kHz\n", mclk);

	/* Determine if we should use MCLK instead of VCLK, and if so, what we
	 * should divide it by to get VCLK
	 */

	if (abs(freq - mclk) < 250) {
		dev_dbg(info->device, "Using VCLK = MCLK\n");
		return 1;
	} else if (abs(freq - (mclk / 2)) < 250) {
		dev_dbg(info->device, "Using VCLK = MCLK/2\n");
		return 2;
	}

	return 0;
}