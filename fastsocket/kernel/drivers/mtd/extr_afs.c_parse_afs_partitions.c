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
typedef  scalar_t__ u_int ;
struct mtd_partition {char* name; int size; scalar_t__ mask_flags; scalar_t__ offset; } ;
struct mtd_info {scalar_t__ size; scalar_t__ erasesize; } ;
struct image_info_struct {int length; int /*<<< orphan*/  name; int /*<<< orphan*/  imageNumber; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int afs_read_footer (struct mtd_info*,scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 
 int afs_read_iis (struct mtd_info*,struct image_info_struct*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mtd_partition*) ; 
 struct mtd_partition* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_afs_partitions(struct mtd_info *mtd,
                         struct mtd_partition **pparts,
                         unsigned long origin)
{
	struct mtd_partition *parts;
	u_int mask, off, idx, sz;
	int ret = 0;
	char *str;

	/*
	 * This is the address mask; we use this to mask off out of
	 * range address bits.
	 */
	mask = mtd->size - 1;

	/*
	 * First, calculate the size of the array we need for the
	 * partition information.  We include in this the size of
	 * the strings.
	 */
	for (idx = off = sz = 0; off < mtd->size; off += mtd->erasesize) {
		struct image_info_struct iis;
		u_int iis_ptr, img_ptr;

		ret = afs_read_footer(mtd, &img_ptr, &iis_ptr, off, mask);
		if (ret < 0)
			break;
		if (ret == 0)
			continue;

		ret = afs_read_iis(mtd, &iis, iis_ptr);
		if (ret < 0)
			break;
		if (ret == 0)
			continue;

		sz += sizeof(struct mtd_partition);
		sz += strlen(iis.name) + 1;
		idx += 1;
	}

	if (!sz)
		return ret;

	parts = kzalloc(sz, GFP_KERNEL);
	if (!parts)
		return -ENOMEM;

	str = (char *)(parts + idx);

	/*
	 * Identify the partitions
	 */
	for (idx = off = 0; off < mtd->size; off += mtd->erasesize) {
		struct image_info_struct iis;
		u_int iis_ptr, img_ptr;

		/* Read the footer. */
		ret = afs_read_footer(mtd, &img_ptr, &iis_ptr, off, mask);
		if (ret < 0)
			break;
		if (ret == 0)
			continue;

		/* Read the image info block */
		ret = afs_read_iis(mtd, &iis, iis_ptr);
		if (ret < 0)
			break;
		if (ret == 0)
			continue;

		strcpy(str, iis.name);

		parts[idx].name		= str;
		parts[idx].size		= (iis.length + mtd->erasesize - 1) & ~(mtd->erasesize - 1);
		parts[idx].offset	= img_ptr;
		parts[idx].mask_flags	= 0;

		printk("  mtd%d: at 0x%08x, %5lluKiB, %8u, %s\n",
			idx, img_ptr, parts[idx].size / 1024,
			iis.imageNumber, str);

		idx += 1;
		str = str + strlen(iis.name) + 1;
	}

	if (!idx) {
		kfree(parts);
		parts = NULL;
	}

	*pparts = parts;
	return idx ? idx : ret;
}