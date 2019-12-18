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
struct my_timming {scalar_t__ crtc; int /*<<< orphan*/  mnp; int /*<<< orphan*/  pixclock; } ;
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ MATROXFB_SRC_CRTC1 ; 
 int /*<<< orphan*/  M_PIXEL_PLL_C ; 
 int /*<<< orphan*/  M_VIDEO_PLL ; 
 int /*<<< orphan*/  g450_mnp2f (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matroxfb_g450_setclk (struct matrox_fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g450_dvi_compute(void* md, struct my_timming* mt) {
	struct matrox_fb_info *minfo = md;

	if (mt->mnp < 0) {
		mt->mnp = matroxfb_g450_setclk(minfo, mt->pixclock, (mt->crtc == MATROXFB_SRC_CRTC1) ? M_PIXEL_PLL_C : M_VIDEO_PLL);
		mt->pixclock = g450_mnp2f(minfo, mt->mnp);
	}
	return 0;
}