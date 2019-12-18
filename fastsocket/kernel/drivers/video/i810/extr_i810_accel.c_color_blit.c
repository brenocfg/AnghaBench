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
struct i810fb_par {int dummy; } ;
struct fb_info {struct i810fb_par* par; } ;

/* Variables and functions */
 int BLIT ; 
 int COLOR_BLT ; 
 int DYN_COLOR_EN ; 
 scalar_t__ IRING_PAD ; 
 int NOP ; 
 int /*<<< orphan*/  PUT_RING (int) ; 
 int SOLIDPATTERN ; 
 scalar_t__ begin_iring (struct fb_info*,scalar_t__) ; 
 int /*<<< orphan*/  end_iring (struct i810fb_par*) ; 

__attribute__((used)) static inline void color_blit(int width, int height, int pitch,  int dest, 
			      int rop, int what, int blit_bpp, 
			      struct fb_info *info)
{
	struct i810fb_par *par = info->par;

	if (begin_iring(info, 24 + IRING_PAD)) return;

	PUT_RING(BLIT | COLOR_BLT | 3);
	PUT_RING(rop << 16 | pitch | SOLIDPATTERN | DYN_COLOR_EN | blit_bpp);
	PUT_RING(height << 16 | width);
	PUT_RING(dest);
	PUT_RING(what);
	PUT_RING(NOP);

	end_iring(par);
}