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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_pm_tbl_entry {scalar_t__ tCWL; int tRP; int tRAS; int tRFC; int tRC; int tRCDWR; int tRCDRD; int tCL; int tWR; int tWTR; int tUNK_20; int tUNK_21; int tUNK_13; int tRRD; } ;
struct nouveau_pm_memtiming {scalar_t__ tCWL; int* reg; int /*<<< orphan*/  id; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,...) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int
nvc0_mem_timing_calc(struct drm_device *dev, u32 freq,
		     struct nouveau_pm_tbl_entry *e, u8 len,
		     struct nouveau_pm_memtiming *boot,
		     struct nouveau_pm_memtiming *t)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (e->tCWL > 0)
		t->tCWL = e->tCWL;

	t->reg[0] = (e->tRP << 24 | (e->tRAS & 0x7f) << 17 |
		     e->tRFC << 8 | e->tRC);

	t->reg[1] = (boot->reg[1] & 0xff000000) |
		    (e->tRCDWR & 0x0f) << 20 |
		    (e->tRCDRD & 0x0f) << 14 |
		    (t->tCWL << 7) |
		    (e->tCL & 0x0f);

	t->reg[2] = (boot->reg[2] & 0xff0000ff) |
		    e->tWR << 16 | e->tWTR << 8;

	t->reg[3] = (e->tUNK_20 & 0x1f) << 9 |
		    (e->tUNK_21 & 0xf) << 5 |
		    (e->tUNK_13 & 0x1f);

	t->reg[4] = (boot->reg[4] & 0xfff00fff) |
		    (e->tRRD&0x1f) << 15;

	NV_DEBUG(drm, "Entry %d: 290: %08x %08x %08x %08x\n", t->id,
		 t->reg[0], t->reg[1], t->reg[2], t->reg[3]);
	NV_DEBUG(drm, "         2a0: %08x\n", t->reg[4]);
	return 0;
}