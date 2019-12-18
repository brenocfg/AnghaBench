#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  base; int /*<<< orphan*/  vbase; } ;
struct TYPE_5__ {int len_maximum; int /*<<< orphan*/  base; int /*<<< orphan*/  vbase; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  vram; scalar_t__ vram_valid; } ;
struct matrox_fb_info {int dead; TYPE_3__ mmio; TYPE_2__ video; TYPE_1__ mtrr; int /*<<< orphan*/  fbcon; scalar_t__ usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct matrox_fb_info*) ; 
 int /*<<< orphan*/  matroxfb_g450_shutdown (struct matrox_fb_info*) ; 
 int /*<<< orphan*/  matroxfb_unregister_device (struct matrox_fb_info*) ; 
 int /*<<< orphan*/  mga_iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void matroxfb_remove(struct matrox_fb_info *minfo, int dummy)
{
	/* Currently we are holding big kernel lock on all dead & usecount updates.
	 * Destroy everything after all users release it. Especially do not unregister
	 * framebuffer and iounmap memory, neither fbmem nor fbcon-cfb* does not check
	 * for device unplugged when in use.
	 * In future we should point mmio.vbase & video.vbase somewhere where we can
	 * write data without causing too much damage...
	 */

	minfo->dead = 1;
	if (minfo->usecount) {
		/* destroy it later */
		return;
	}
	matroxfb_unregister_device(minfo);
	unregister_framebuffer(&minfo->fbcon);
	matroxfb_g450_shutdown(minfo);
#ifdef CONFIG_MTRR
	if (minfo->mtrr.vram_valid)
		mtrr_del(minfo->mtrr.vram, minfo->video.base, minfo->video.len);
#endif
	mga_iounmap(minfo->mmio.vbase);
	mga_iounmap(minfo->video.vbase);
	release_mem_region(minfo->video.base, minfo->video.len_maximum);
	release_mem_region(minfo->mmio.base, 16384);
	kfree(minfo);
}