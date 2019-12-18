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
struct nouveau_pm_tbl_entry {int tRP; int tRAS; int tRFC; int tRC; int tWR; int tWTR; int tCL; int tRRD; int tRCDWR; int tRCDRD; } ;
struct nouveau_pm_memtiming {int* reg; int tCWL; int /*<<< orphan*/  id; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int
nv40_mem_timing_calc(struct drm_device *dev, u32 freq,
		     struct nouveau_pm_tbl_entry *e, u8 len,
		     struct nouveau_pm_memtiming *boot,
		     struct nouveau_pm_memtiming *t)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	t->reg[0] = (e->tRP << 24 | e->tRAS << 16 | e->tRFC << 8 | e->tRC);

	/* XXX: I don't trust the -1's and +1's... they must come
	 *      from somewhere! */
	t->reg[1] = (e->tWR + 2 + (t->tCWL - 1)) << 24 |
		    1 << 16 |
		    (e->tWTR + 2 + (t->tCWL - 1)) << 8 |
		    (e->tCL + 2 - (t->tCWL - 1));

	t->reg[2] = 0x20200000 |
		    ((t->tCWL - 1) << 24 |
		     e->tRRD << 16 |
		     e->tRCDWR << 8 |
		     e->tRCDRD);

	NV_DEBUG(drm, "Entry %d: 220: %08x %08x %08x\n", t->id,
		 t->reg[0], t->reg[1], t->reg[2]);
	return 0;
}