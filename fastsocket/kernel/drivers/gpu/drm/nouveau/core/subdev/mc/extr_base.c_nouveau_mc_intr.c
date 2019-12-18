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
typedef  int u32 ;
struct nouveau_subdev {int /*<<< orphan*/  (* intr ) (struct nouveau_subdev*) ;} ;
struct nouveau_mc_intr {int stat; int /*<<< orphan*/  unit; } ;
struct nouveau_mc {struct nouveau_mc_intr* intr_map; } ;

/* Variables and functions */
 struct nouveau_mc* nouveau_mc (struct nouveau_subdev*) ; 
 struct nouveau_subdev* nouveau_subdev (struct nouveau_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_mc*,char*,int) ; 
 int nv_rd32 (struct nouveau_mc*,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_subdev*) ; 

void
nouveau_mc_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_mc *pmc = nouveau_mc(subdev);
	const struct nouveau_mc_intr *map = pmc->intr_map;
	struct nouveau_subdev *unit;
	u32 stat, intr;

	intr = stat = nv_rd32(pmc, 0x000100);
	while (stat && map->stat) {
		if (stat & map->stat) {
			unit = nouveau_subdev(subdev, map->unit);
			if (unit && unit->intr)
				unit->intr(unit);
			intr &= ~map->stat;
		}
		map++;
	}

	if (intr) {
		nv_error(pmc, "unknown intr 0x%08x\n", stat);
	}
}