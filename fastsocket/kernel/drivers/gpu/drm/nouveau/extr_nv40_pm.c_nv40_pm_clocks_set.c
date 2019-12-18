#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nv40_pm_state {int npll_coef; int npll_ctrl; int spll; int ctrl; int mpll_ctrl; int mpll_coef; } ;
struct nouveau_fifo {int /*<<< orphan*/  (* start ) (struct nouveau_fifo*,unsigned long*) ;int /*<<< orphan*/  (* pause ) (struct nouveau_fifo*,unsigned long*) ;} ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ROM16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bit_table (struct drm_device*,char,struct bit_entry*) ; 
 int /*<<< orphan*/  kfree (struct nv40_pm_state*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  nouveau_bios_run_init_table (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_device*) ; 
 int /*<<< orphan*/  nv40_pm_gr_idle ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_device*,int,int,int) ; 
 int nv_rd08 (struct nouveau_device*,int) ; 
 scalar_t__ nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_device*,int,int,int) ; 
 int /*<<< orphan*/  nv_wait_cb (struct nouveau_device*,int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  nv_wr08 (struct nouveau_device*,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_fifo*,unsigned long*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
nv40_pm_clocks_set(struct drm_device *dev, void *pre_state)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_fifo *pfifo = nouveau_fifo(device);
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nv40_pm_state *info = pre_state;
	unsigned long flags;
	struct bit_entry M;
	u32 crtc_mask = 0;
	u8 sr1[2];
	int i, ret = -EAGAIN;

	/* determine which CRTCs are active, fetch VGA_SR1 for each */
	for (i = 0; i < 2; i++) {
		u32 vbl = nv_rd32(device, 0x600808 + (i * 0x2000));
		u32 cnt = 0;
		do {
			if (vbl != nv_rd32(device, 0x600808 + (i * 0x2000))) {
				nv_wr08(device, 0x0c03c4 + (i * 0x2000), 0x01);
				sr1[i] = nv_rd08(device, 0x0c03c5 + (i * 0x2000));
				if (!(sr1[i] & 0x20))
					crtc_mask |= (1 << i);
				break;
			}
			udelay(1);
		} while (cnt++ < 32);
	}

	/* halt and idle engines */
	pfifo->pause(pfifo, &flags);

	if (!nv_wait_cb(device, nv40_pm_gr_idle, dev))
		goto resume;

	ret = 0;

	/* set engine clocks */
	nv_mask(device, 0x00c040, 0x00000333, 0x00000000);
	nv_wr32(device, 0x004004, info->npll_coef);
	nv_mask(device, 0x004000, 0xc0070100, info->npll_ctrl);
	nv_mask(device, 0x004008, 0xc007ffff, info->spll);
	mdelay(5);
	nv_mask(device, 0x00c040, 0x00000333, info->ctrl);

	if (!info->mpll_ctrl)
		goto resume;

	/* wait for vblank start on active crtcs, disable memory access */
	for (i = 0; i < 2; i++) {
		if (!(crtc_mask & (1 << i)))
			continue;
		nv_wait(device, 0x600808 + (i * 0x2000), 0x00010000, 0x00000000);
		nv_wait(device, 0x600808 + (i * 0x2000), 0x00010000, 0x00010000);
		nv_wr08(device, 0x0c03c4 + (i * 0x2000), 0x01);
		nv_wr08(device, 0x0c03c5 + (i * 0x2000), sr1[i] | 0x20);
	}

	/* prepare ram for reclocking */
	nv_wr32(device, 0x1002d4, 0x00000001); /* precharge */
	nv_wr32(device, 0x1002d0, 0x00000001); /* refresh */
	nv_wr32(device, 0x1002d0, 0x00000001); /* refresh */
	nv_mask(device, 0x100210, 0x80000000, 0x00000000); /* no auto refresh */
	nv_wr32(device, 0x1002dc, 0x00000001); /* enable self-refresh */

	/* change the PLL of each memory partition */
	nv_mask(device, 0x00c040, 0x0000c000, 0x00000000);
	switch (nv_device(drm->device)->chipset) {
	case 0x40:
	case 0x45:
	case 0x41:
	case 0x42:
	case 0x47:
		nv_mask(device, 0x004044, 0xc0771100, info->mpll_ctrl);
		nv_mask(device, 0x00402c, 0xc0771100, info->mpll_ctrl);
		nv_wr32(device, 0x004048, info->mpll_coef);
		nv_wr32(device, 0x004030, info->mpll_coef);
	case 0x43:
	case 0x49:
	case 0x4b:
		nv_mask(device, 0x004038, 0xc0771100, info->mpll_ctrl);
		nv_wr32(device, 0x00403c, info->mpll_coef);
	default:
		nv_mask(device, 0x004020, 0xc0771100, info->mpll_ctrl);
		nv_wr32(device, 0x004024, info->mpll_coef);
		break;
	}
	udelay(100);
	nv_mask(device, 0x00c040, 0x0000c000, 0x0000c000);

	/* re-enable normal operation of memory controller */
	nv_wr32(device, 0x1002dc, 0x00000000);
	nv_mask(device, 0x100210, 0x80000000, 0x80000000);
	udelay(100);

	/* execute memory reset script from vbios */
	if (!bit_table(dev, 'M', &M))
		nouveau_bios_run_init_table(dev, ROM16(M.data[0]), NULL, 0);

	/* make sure we're in vblank (hopefully the same one as before), and
	 * then re-enable crtc memory access
	 */
	for (i = 0; i < 2; i++) {
		if (!(crtc_mask & (1 << i)))
			continue;
		nv_wait(device, 0x600808 + (i * 0x2000), 0x00010000, 0x00010000);
		nv_wr08(device, 0x0c03c4 + (i * 0x2000), 0x01);
		nv_wr08(device, 0x0c03c5 + (i * 0x2000), sr1[i]);
	}

	/* resume engines */
resume:
	pfifo->start(pfifo, &flags);
	kfree(info);
	return ret;
}