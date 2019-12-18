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
struct mtd_info {scalar_t__ size; struct map_info* priv; } ;
struct map_info {scalar_t__ virt; struct lpddr_private* fldrv_priv; } ;
struct lpddr_private {scalar_t__ chipshift; int numchips; struct flchip* chips; } ;
struct flchip {long start; int /*<<< orphan*/  ref_point_counter; int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FL_POINT ; 
 int get_chip (struct map_info*,struct flchip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpddr_point(struct mtd_info *mtd, loff_t adr, size_t len,
			size_t *retlen, void **mtdbuf, resource_size_t *phys)
{
	struct map_info *map = mtd->priv;
	struct lpddr_private *lpddr = map->fldrv_priv;
	int chipnum = adr >> lpddr->chipshift;
	unsigned long ofs, last_end = 0;
	struct flchip *chip = &lpddr->chips[chipnum];
	int ret = 0;

	if (!map->virt || (adr + len > mtd->size))
		return -EINVAL;

	/* ofs: offset within the first chip that the first read should start */
	ofs = adr - (chipnum << lpddr->chipshift);

	*mtdbuf = (void *)map->virt + chip->start + ofs;
	*retlen = 0;

	while (len) {
		unsigned long thislen;

		if (chipnum >= lpddr->numchips)
			break;

		/* We cannot point across chips that are virtually disjoint */
		if (!last_end)
			last_end = chip->start;
		else if (chip->start != last_end)
			break;

		if ((len + ofs - 1) >> lpddr->chipshift)
			thislen = (1<<lpddr->chipshift) - ofs;
		else
			thislen = len;
		/* get the chip */
		spin_lock(chip->mutex);
		ret = get_chip(map, chip, FL_POINT);
		spin_unlock(chip->mutex);
		if (ret)
			break;

		chip->state = FL_POINT;
		chip->ref_point_counter++;
		*retlen += thislen;
		len -= thislen;

		ofs = 0;
		last_end += 1 << lpddr->chipshift;
		chipnum++;
		chip = &lpddr->chips[chipnum];
	}
	return 0;
}