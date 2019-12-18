#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_8__ {TYPE_3__ vsync; } ;
struct TYPE_5__ {scalar_t__ yres; } ;
struct TYPE_6__ {TYPE_1__ var; } ;
struct matrox_fb_info {TYPE_4__ crtc1; int /*<<< orphan*/  irq_flags; TYPE_2__ fbcon; } ;
struct fb_vblank {int flags; scalar_t__ vcount; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int FB_VBLANK_HAVE_COUNT ; 
 int FB_VBLANK_HAVE_HBLANK ; 
 int FB_VBLANK_HAVE_VBLANK ; 
 int FB_VBLANK_HAVE_VCOUNT ; 
 int FB_VBLANK_HAVE_VSYNC ; 
 int FB_VBLANK_HBLANKING ; 
 int FB_VBLANK_VBLANKING ; 
 int FB_VBLANK_VSYNCING ; 
 int /*<<< orphan*/  M_INSTS1 ; 
 int /*<<< orphan*/  M_VCOUNT ; 
 int /*<<< orphan*/  matroxfb_enable_irq (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fb_vblank*,int /*<<< orphan*/ ,int) ; 
 unsigned int mga_inb (int /*<<< orphan*/ ) ; 
 scalar_t__ mga_inl (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int matroxfb_get_vblank(struct matrox_fb_info *minfo,
			       struct fb_vblank *vblank)
{
	unsigned int sts1;

	matroxfb_enable_irq(minfo, 0);
	memset(vblank, 0, sizeof(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VCOUNT | FB_VBLANK_HAVE_VSYNC |
			FB_VBLANK_HAVE_VBLANK | FB_VBLANK_HAVE_HBLANK;
	sts1 = mga_inb(M_INSTS1);
	vblank->vcount = mga_inl(M_VCOUNT);
	/* BTW, on my PIII/450 with G400, reading M_INSTS1
	   byte makes this call about 12% slower (1.70 vs. 2.05 us
	   per ioctl()) */
	if (sts1 & 1)
		vblank->flags |= FB_VBLANK_HBLANKING;
	if (sts1 & 8)
		vblank->flags |= FB_VBLANK_VSYNCING;
	if (vblank->vcount >= minfo->fbcon.var.yres)
		vblank->flags |= FB_VBLANK_VBLANKING;
	if (test_bit(0, &minfo->irq_flags)) {
		vblank->flags |= FB_VBLANK_HAVE_COUNT;
		/* Only one writer, aligned int value...
		   it should work without lock and without atomic_t */
		vblank->count = minfo->crtc1.vsync.cnt;
	}
	return 0;
}