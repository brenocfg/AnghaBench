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
typedef  void* uint64_t ;
struct mtd_info {int flags; scalar_t__ size; } ;
struct mtd_erase_region_info {scalar_t__ offset; int erasesize; } ;
struct TYPE_2__ {scalar_t__ size; int numeraseregions; int erasesize; struct mtd_erase_region_info* eraseregions; } ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; TYPE_1__ mtd; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; scalar_t__ fail_addr; int /*<<< orphan*/  (* callback ) (struct erase_info*) ;int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MTD_FAIL_ADDR_UNKNOWN ; 
 int MTD_WRITEABLE ; 
 int concat_dev_erase (struct mtd_info*,struct erase_info*) ; 
 int /*<<< orphan*/  kfree (struct erase_info*) ; 
 struct erase_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct erase_info*) ; 

__attribute__((used)) static int concat_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct mtd_concat *concat = CONCAT(mtd);
	struct mtd_info *subdev;
	int i, err;
	uint64_t length, offset = 0;
	struct erase_info *erase;

	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;

	if (instr->addr > concat->mtd.size)
		return -EINVAL;

	if (instr->len + instr->addr > concat->mtd.size)
		return -EINVAL;

	/*
	 * Check for proper erase block alignment of the to-be-erased area.
	 * It is easier to do this based on the super device's erase
	 * region info rather than looking at each particular sub-device
	 * in turn.
	 */
	if (!concat->mtd.numeraseregions) {
		/* the easy case: device has uniform erase block size */
		if (instr->addr & (concat->mtd.erasesize - 1))
			return -EINVAL;
		if (instr->len & (concat->mtd.erasesize - 1))
			return -EINVAL;
	} else {
		/* device has variable erase size */
		struct mtd_erase_region_info *erase_regions =
		    concat->mtd.eraseregions;

		/*
		 * Find the erase region where the to-be-erased area begins:
		 */
		for (i = 0; i < concat->mtd.numeraseregions &&
		     instr->addr >= erase_regions[i].offset; i++) ;
		--i;

		/*
		 * Now erase_regions[i] is the region in which the
		 * to-be-erased area begins. Verify that the starting
		 * offset is aligned to this region's erase size:
		 */
		if (i < 0 || instr->addr & (erase_regions[i].erasesize - 1))
			return -EINVAL;

		/*
		 * now find the erase region where the to-be-erased area ends:
		 */
		for (; i < concat->mtd.numeraseregions &&
		     (instr->addr + instr->len) >= erase_regions[i].offset;
		     ++i) ;
		--i;
		/*
		 * check if the ending offset is aligned to this region's erase size
		 */
		if (i < 0 || ((instr->addr + instr->len) &
					(erase_regions[i].erasesize - 1)))
			return -EINVAL;
	}

	instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;

	/* make a local copy of instr to avoid modifying the caller's struct */
	erase = kmalloc(sizeof (struct erase_info), GFP_KERNEL);

	if (!erase)
		return -ENOMEM;

	*erase = *instr;
	length = instr->len;

	/*
	 * find the subdevice where the to-be-erased area begins, adjust
	 * starting offset to be relative to the subdevice start
	 */
	for (i = 0; i < concat->num_subdev; i++) {
		subdev = concat->subdev[i];
		if (subdev->size <= erase->addr) {
			erase->addr -= subdev->size;
			offset += subdev->size;
		} else {
			break;
		}
	}

	/* must never happen since size limit has been verified above */
	BUG_ON(i >= concat->num_subdev);

	/* now do the erase: */
	err = 0;
	for (; length > 0; i++) {
		/* loop for all subdevices affected by this request */
		subdev = concat->subdev[i];	/* get current subdevice */

		/* limit length to subdevice's size: */
		if (erase->addr + length > subdev->size)
			erase->len = subdev->size - erase->addr;
		else
			erase->len = length;

		if (!(subdev->flags & MTD_WRITEABLE)) {
			err = -EROFS;
			break;
		}
		length -= erase->len;
		if ((err = concat_dev_erase(subdev, erase))) {
			/* sanity check: should never happen since
			 * block alignment has been checked above */
			BUG_ON(err == -EINVAL);
			if (erase->fail_addr != MTD_FAIL_ADDR_UNKNOWN)
				instr->fail_addr = erase->fail_addr + offset;
			break;
		}
		/*
		 * erase->addr specifies the offset of the area to be
		 * erased *within the current subdevice*. It can be
		 * non-zero only the first time through this loop, i.e.
		 * for the first subdevice where blocks need to be erased.
		 * All the following erases must begin at the start of the
		 * current subdevice, i.e. at offset zero.
		 */
		erase->addr = 0;
		offset += subdev->size;
	}
	instr->state = erase->state;
	kfree(erase);
	if (err)
		return err;

	if (instr->callback)
		instr->callback(instr);
	return 0;
}