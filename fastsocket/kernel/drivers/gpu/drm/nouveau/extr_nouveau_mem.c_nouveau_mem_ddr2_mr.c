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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_pm_tbl_entry {int RAM_FT1; int tCL; int tWR; } ;
struct nouveau_pm_memtiming {int odt; int* mr; int /*<<< orphan*/  id; scalar_t__ drive_strength; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int) ; 
 int NV_MEM_CL_DDR2_MAX ; 
 int NV_MEM_WR_DDR2_MAX ; 
 int /*<<< orphan*/  NV_WARN (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int
nouveau_mem_ddr2_mr(struct drm_device *dev, u32 freq,
		    struct nouveau_pm_tbl_entry *e, u8 len,
		    struct nouveau_pm_memtiming *boot,
		    struct nouveau_pm_memtiming *t)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	t->drive_strength = 0;
	if (len < 15) {
		t->odt = boot->odt;
	} else {
		t->odt = e->RAM_FT1 & 0x07;
	}

	if (e->tCL >= NV_MEM_CL_DDR2_MAX) {
		NV_WARN(drm, "(%u) Invalid tCL: %u", t->id, e->tCL);
		return -ERANGE;
	}

	if (e->tWR >= NV_MEM_WR_DDR2_MAX) {
		NV_WARN(drm, "(%u) Invalid tWR: %u", t->id, e->tWR);
		return -ERANGE;
	}

	if (t->odt > 3) {
		NV_WARN(drm, "(%u) Invalid odt value, assuming disabled: %x",
			t->id, t->odt);
		t->odt = 0;
	}

	t->mr[0] = (boot->mr[0] & 0x100f) |
		   (e->tCL) << 4 |
		   (e->tWR - 1) << 9;
	t->mr[1] = (boot->mr[1] & 0x101fbb) |
		   (t->odt & 0x1) << 2 |
		   (t->odt & 0x2) << 5;

	NV_DEBUG(drm, "(%u) MR: %08x", t->id, t->mr[0]);
	return 0;
}