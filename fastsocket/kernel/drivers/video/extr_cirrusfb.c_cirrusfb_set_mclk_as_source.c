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
 int /*<<< orphan*/  CL_SEQR1E ; 
 int /*<<< orphan*/  CL_SEQR1F ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int vga_rseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void cirrusfb_set_mclk_as_source(const struct fb_info *info, int div)
{
	struct cirrusfb_info *cinfo = info->par;
	unsigned char old1f, old1e;

	assert(cinfo != NULL);
	old1f = vga_rseq(cinfo->regbase, CL_SEQR1F) & ~0x40;

	if (div) {
		dev_dbg(info->device, "Set %s as pixclock source.\n",
			(div == 2) ? "MCLK/2" : "MCLK");
		old1f |= 0x40;
		old1e = vga_rseq(cinfo->regbase, CL_SEQR1E) & ~0x1;
		if (div == 2)
			old1e |= 1;

		vga_wseq(cinfo->regbase, CL_SEQR1E, old1e);
	}
	vga_wseq(cinfo->regbase, CL_SEQR1F, old1f);
}