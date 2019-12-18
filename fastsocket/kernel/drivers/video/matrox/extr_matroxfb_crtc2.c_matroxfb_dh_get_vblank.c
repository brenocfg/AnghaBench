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
struct TYPE_5__ {int yres; } ;
struct TYPE_6__ {TYPE_1__ var; } ;
struct matroxfb_dh_fb_info {TYPE_2__ fbcon; struct matrox_fb_info* primary_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_8__ {TYPE_3__ vsync; } ;
struct matrox_fb_info {TYPE_4__ crtc2; int /*<<< orphan*/  irq_flags; } ;
struct fb_vblank {int flags; int vcount; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int FB_VBLANK_HAVE_COUNT ; 
 int FB_VBLANK_HAVE_VBLANK ; 
 int FB_VBLANK_HAVE_VCOUNT ; 
 int FB_VBLANK_VBLANKING ; 
 int /*<<< orphan*/  matroxfb_enable_irq (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fb_vblank*,int /*<<< orphan*/ ,int) ; 
 int mga_inl (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int matroxfb_dh_get_vblank(const struct matroxfb_dh_fb_info* m2info, struct fb_vblank* vblank) {
	struct matrox_fb_info *minfo = m2info->primary_dev;

	matroxfb_enable_irq(minfo, 0);
	memset(vblank, 0, sizeof(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VCOUNT | FB_VBLANK_HAVE_VBLANK;
	/* mask out reserved bits + field number (odd/even) */
	vblank->vcount = mga_inl(0x3C48) & 0x000007FF;
	/* compatibility stuff */
	if (vblank->vcount >= m2info->fbcon.var.yres)
		vblank->flags |= FB_VBLANK_VBLANKING;
	if (test_bit(0, &minfo->irq_flags)) {
                vblank->flags |= FB_VBLANK_HAVE_COUNT;
                /* Only one writer, aligned int value...
                   it should work without lock and without atomic_t */
		vblank->count = minfo->crtc2.vsync.cnt;
        }
	return 0;
}