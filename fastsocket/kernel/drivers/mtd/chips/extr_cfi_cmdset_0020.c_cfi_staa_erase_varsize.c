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
struct mtd_info {scalar_t__ size; int numeraseregions; struct mtd_erase_region_info* eraseregions; struct map_info* priv; } ;
struct mtd_erase_region_info {scalar_t__ offset; int erasesize; unsigned long numblocks; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; int /*<<< orphan*/  state; } ;
struct cfi_private {int chipshift; int numchips; int /*<<< orphan*/ * chips; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTD_ERASE_DONE ; 
 int do_erase_oneblock (struct map_info*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mtd_erase_callback (struct erase_info*) ; 

__attribute__((used)) static int cfi_staa_erase_varsize(struct mtd_info *mtd,
				  struct erase_info *instr)
{	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long adr, len;
	int chipnum, ret = 0;
	int i, first;
	struct mtd_erase_region_info *regions = mtd->eraseregions;

	if (instr->addr > mtd->size)
		return -EINVAL;

	if ((instr->len + instr->addr) > mtd->size)
		return -EINVAL;

	/* Check that both start and end of the requested erase are
	 * aligned with the erasesize at the appropriate addresses.
	 */

	i = 0;

	/* Skip all erase regions which are ended before the start of
	   the requested erase. Actually, to save on the calculations,
	   we skip to the first erase region which starts after the
	   start of the requested erase, and then go back one.
	*/

	while (i < mtd->numeraseregions && instr->addr >= regions[i].offset)
	       i++;
	i--;

	/* OK, now i is pointing at the erase region in which this
	   erase request starts. Check the start of the requested
	   erase range is aligned with the erase size which is in
	   effect here.
	*/

	if (instr->addr & (regions[i].erasesize-1))
		return -EINVAL;

	/* Remember the erase region we start on */
	first = i;

	/* Next, check that the end of the requested erase is aligned
	 * with the erase region at that address.
	 */

	while (i<mtd->numeraseregions && (instr->addr + instr->len) >= regions[i].offset)
		i++;

	/* As before, drop back one to point at the region in which
	   the address actually falls
	*/
	i--;

	if ((instr->addr + instr->len) & (regions[i].erasesize-1))
		return -EINVAL;

	chipnum = instr->addr >> cfi->chipshift;
	adr = instr->addr - (chipnum << cfi->chipshift);
	len = instr->len;

	i=first;

	while(len) {
		ret = do_erase_oneblock(map, &cfi->chips[chipnum], adr);

		if (ret)
			return ret;

		adr += regions[i].erasesize;
		len -= regions[i].erasesize;

		if (adr % (1<< cfi->chipshift) == (((unsigned long)regions[i].offset + (regions[i].erasesize * regions[i].numblocks)) %( 1<< cfi->chipshift)))
			i++;

		if (adr >> cfi->chipshift) {
			adr = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
			break;
		}
	}

	instr->state = MTD_ERASE_DONE;
	mtd_erase_callback(instr);

	return 0;
}