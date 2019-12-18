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
struct mtd_info {int writesize; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  flags; int /*<<< orphan*/  erase; int /*<<< orphan*/  sync; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  get_unmapped_area; int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct map_info* priv; } ;
struct map_info {int /*<<< orphan*/  size; int /*<<< orphan*/  name; int /*<<< orphan*/ * fldrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_CAP_ROM ; 
 int /*<<< orphan*/  MTD_ROM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct mtd_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maprom_chipdrv ; 
 int /*<<< orphan*/  maprom_erase ; 
 int /*<<< orphan*/  maprom_nop ; 
 int /*<<< orphan*/  maprom_read ; 
 int /*<<< orphan*/  maprom_unmapped_area ; 
 int /*<<< orphan*/  maprom_write ; 

__attribute__((used)) static struct mtd_info *map_rom_probe(struct map_info *map)
{
	struct mtd_info *mtd;

	mtd = kzalloc(sizeof(*mtd), GFP_KERNEL);
	if (!mtd)
		return NULL;

	map->fldrv = &maprom_chipdrv;
	mtd->priv = map;
	mtd->name = map->name;
	mtd->type = MTD_ROM;
	mtd->size = map->size;
	mtd->get_unmapped_area = maprom_unmapped_area;
	mtd->read = maprom_read;
	mtd->write = maprom_write;
	mtd->sync = maprom_nop;
	mtd->erase = maprom_erase;
	mtd->flags = MTD_CAP_ROM;
	mtd->erasesize = map->size;
	mtd->writesize = 1;

	__module_get(THIS_MODULE);
	return mtd;
}