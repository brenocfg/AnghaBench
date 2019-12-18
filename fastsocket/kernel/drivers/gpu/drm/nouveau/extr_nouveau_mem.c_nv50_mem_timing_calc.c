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
typedef  int uint8_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_pm_tbl_entry {int tUNK_21; int tUNK_20; int tCWL; int tUNK_18; int tRP; int tRAS; int tRFC; int tRC; int tWR; int tWTR; int tRRD; int tRCDWR; int tRCDRD; int tUNK_13; int tCL; } ;
struct nouveau_pm_memtiming {int tCWL; int* reg; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct nouveau_fb {TYPE_1__ ram; } ;
struct nouveau_drm {int dummy; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int version; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,...) ; 
 scalar_t__ NV_MEM_TYPE_DDR2 ; 
 scalar_t__ bit_table (struct drm_device*,char,struct bit_entry*) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_device*) ; 

__attribute__((used)) static int
nv50_mem_timing_calc(struct drm_device *dev, u32 freq,
		     struct nouveau_pm_tbl_entry *e, u8 len,
		     struct nouveau_pm_memtiming *boot,
		     struct nouveau_pm_memtiming *t)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_fb *pfb = nouveau_fb(device);
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct bit_entry P;
	uint8_t unk18 = 1, unk20 = 0, unk21 = 0, tmp7_3;

	if (bit_table(dev, 'P', &P))
		return -EINVAL;

	switch (min(len, (u8) 22)) {
	case 22:
		unk21 = e->tUNK_21;
	case 21:
		unk20 = e->tUNK_20;
	case 20:
		if (e->tCWL > 0)
			t->tCWL = e->tCWL;
	case 19:
		unk18 = e->tUNK_18;
		break;
	}

	t->reg[0] = (e->tRP << 24 | e->tRAS << 16 | e->tRFC << 8 | e->tRC);

	t->reg[1] = (e->tWR + 2 + (t->tCWL - 1)) << 24 |
				max(unk18, (u8) 1) << 16 |
				(e->tWTR + 2 + (t->tCWL - 1)) << 8;

	t->reg[2] = ((t->tCWL - 1) << 24 |
		    e->tRRD << 16 |
		    e->tRCDWR << 8 |
		    e->tRCDRD);

	t->reg[4] = e->tUNK_13 << 8  | e->tUNK_13;

	t->reg[5] = (e->tRFC << 24 | max(e->tRCDRD, e->tRCDWR) << 16 | e->tRP);

	t->reg[8] = boot->reg[8] & 0xffffff00;

	if (P.version == 1) {
		t->reg[1] |= (e->tCL + 2 - (t->tCWL - 1));

		t->reg[3] = (0x14 + e->tCL) << 24 |
			    0x16 << 16 |
			    (e->tCL - 1) << 8 |
			    (e->tCL - 1);

		t->reg[4] |= boot->reg[4] & 0xffff0000;

		t->reg[6] = (0x33 - t->tCWL) << 16 |
			    t->tCWL << 8 |
			    (0x2e + e->tCL - t->tCWL);

		t->reg[7] = 0x4000202 | (e->tCL - 1) << 16;

		/* XXX: P.version == 1 only has DDR2 and GDDR3? */
		if (pfb->ram.type == NV_MEM_TYPE_DDR2) {
			t->reg[5] |= (e->tCL + 3) << 8;
			t->reg[6] |= (t->tCWL - 2) << 8;
			t->reg[8] |= (e->tCL - 4);
		} else {
			t->reg[5] |= (e->tCL + 2) << 8;
			t->reg[6] |= t->tCWL << 8;
			t->reg[8] |= (e->tCL - 2);
		}
	} else {
		t->reg[1] |= (5 + e->tCL - (t->tCWL));

		/* XXX: 0xb? 0x30? */
		t->reg[3] = (0x30 + e->tCL) << 24 |
			    (boot->reg[3] & 0x00ff0000)|
			    (0xb + e->tCL) << 8 |
			    (e->tCL - 1);

		t->reg[4] |= (unk20 << 24 | unk21 << 16);

		/* XXX: +6? */
		t->reg[5] |= (t->tCWL + 6) << 8;

		t->reg[6] = (0x5a + e->tCL) << 16 |
			    (6 - e->tCL + t->tCWL) << 8 |
			    (0x50 + e->tCL - t->tCWL);

		tmp7_3 = (boot->reg[7] & 0xff000000) >> 24;
		t->reg[7] = (tmp7_3 << 24) |
			    ((tmp7_3 - 6 + e->tCL) << 16) |
			    0x202;
	}

	NV_DEBUG(drm, "Entry %d: 220: %08x %08x %08x %08x\n", t->id,
		 t->reg[0], t->reg[1], t->reg[2], t->reg[3]);
	NV_DEBUG(drm, "         230: %08x %08x %08x %08x\n",
		 t->reg[4], t->reg[5], t->reg[6], t->reg[7]);
	NV_DEBUG(drm, "         240: %08x\n", t->reg[8]);
	return 0;
}