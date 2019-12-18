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
typedef  int uint64_t ;
struct mtd_info {int erasesize; int size; struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {int interleave; int device_type; int chipshift; int numchips; int /*<<< orphan*/ * chips; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cfi_read_query (struct map_info*,unsigned long) ; 
 int /*<<< orphan*/  cfi_send_gen_cmd (int,int,int /*<<< orphan*/ ,struct map_info*,struct cfi_private*,int,int /*<<< orphan*/ *) ; 
 int do_lock_oneblock (struct map_info*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfi_staa_lock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long adr;
	int chipnum, ret = 0;
#ifdef DEBUG_LOCK_BITS
	int ofs_factor = cfi->interleave * cfi->device_type;
#endif

	if (ofs & (mtd->erasesize - 1))
		return -EINVAL;

	if (len & (mtd->erasesize -1))
		return -EINVAL;

	if ((len + ofs) > mtd->size)
		return -EINVAL;

	chipnum = ofs >> cfi->chipshift;
	adr = ofs - (chipnum << cfi->chipshift);

	while(len) {

#ifdef DEBUG_LOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NULL);
		printk("before lock: block status register is %x\n",cfi_read_query(map, adr+(2*ofs_factor)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NULL);
#endif

		ret = do_lock_oneblock(map, &cfi->chips[chipnum], adr);

#ifdef DEBUG_LOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NULL);
		printk("after lock: block status register is %x\n",cfi_read_query(map, adr+(2*ofs_factor)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NULL);
#endif

		if (ret)
			return ret;

		adr += mtd->erasesize;
		len -= mtd->erasesize;

		if (adr >> cfi->chipshift) {
			adr = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
			break;
		}
	}
	return 0;
}