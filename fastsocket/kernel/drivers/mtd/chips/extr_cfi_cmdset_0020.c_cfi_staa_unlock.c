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
typedef  unsigned long uint64_t ;
struct mtd_info {scalar_t__ erasesize; struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {int interleave; int device_type; int chipshift; int /*<<< orphan*/ * chips; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  cfi_read_query (struct map_info*,unsigned long) ; 
 int /*<<< orphan*/  cfi_send_gen_cmd (int,int,int /*<<< orphan*/ ,struct map_info*,struct cfi_private*,int,int /*<<< orphan*/ *) ; 
 int do_unlock_oneblock (struct map_info*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,...) ; 

__attribute__((used)) static int cfi_staa_unlock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long adr;
	int chipnum, ret = 0;
#ifdef DEBUG_LOCK_BITS
	int ofs_factor = cfi->interleave * cfi->device_type;
#endif

	chipnum = ofs >> cfi->chipshift;
	adr = ofs - (chipnum << cfi->chipshift);

#ifdef DEBUG_LOCK_BITS
	{
		unsigned long temp_adr = adr;
		unsigned long temp_len = len;

		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NULL);
                while (temp_len) {
			printk("before unlock %x: block status register is %x\n",temp_adr,cfi_read_query(map, temp_adr+(2*ofs_factor)));
			temp_adr += mtd->erasesize;
			temp_len -= mtd->erasesize;
		}
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NULL);
	}
#endif

	ret = do_unlock_oneblock(map, &cfi->chips[chipnum], adr);

#ifdef DEBUG_LOCK_BITS
	cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NULL);
	printk("after unlock: block status register is %x\n",cfi_read_query(map, adr+(2*ofs_factor)));
	cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NULL);
#endif

	return ret;
}