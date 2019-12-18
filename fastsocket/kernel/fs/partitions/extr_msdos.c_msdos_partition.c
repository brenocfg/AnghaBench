#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct partition {int boot_ind; } ;
struct parsed_partitions {int next; TYPE_1__* parts; } ;
struct fat_boot_sector {int /*<<< orphan*/  media; scalar_t__ fats; scalar_t__ reserved; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;
struct TYPE_4__ {unsigned char id; int /*<<< orphan*/  (* parse ) (struct parsed_partitions*,struct block_device*,int,int,int) ;} ;
struct TYPE_3__ {int flags; } ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 unsigned char DM6_PARTITION ; 
 unsigned char EFI_PMBR_OSTYPE_EFI_GPT ; 
 unsigned char EZD_PARTITION ; 
 unsigned char LINUX_RAID_PARTITION ; 
 unsigned char SYS_IND (struct partition*) ; 
 scalar_t__ aix_magic_present (unsigned char*,struct block_device*) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 scalar_t__ fat_valid_media (int /*<<< orphan*/ ) ; 
 scalar_t__ is_extended_partition (struct partition*) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdos_magic_present (unsigned char*) ; 
 int nr_sects (struct partition*) ; 
 int /*<<< orphan*/  parse_extended (struct parsed_partitions*,struct block_device*,int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int,int,int) ; 
 unsigned char* read_dev_sector (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int start_sect (struct partition*) ; 
 int /*<<< orphan*/  stub1 (struct parsed_partitions*,struct block_device*,int,int,int) ; 
 TYPE_2__* subtypes ; 

int msdos_partition(struct parsed_partitions *state, struct block_device *bdev)
{
	sector_t sector_size = bdev_logical_block_size(bdev) / 512;
	Sector sect;
	unsigned char *data;
	struct partition *p;
	struct fat_boot_sector *fb;
	int slot;

	data = read_dev_sector(bdev, 0, &sect);
	if (!data)
		return -1;
	if (!msdos_magic_present(data + 510)) {
		put_dev_sector(sect);
		return 0;
	}

	if (aix_magic_present(data, bdev)) {
		put_dev_sector(sect);
		printk( " [AIX]");
		return 0;
	}

	/*
	 * Now that the 55aa signature is present, this is probably
	 * either the boot sector of a FAT filesystem or a DOS-type
	 * partition table. Reject this in case the boot indicator
	 * is not 0 or 0x80.
	 */
	p = (struct partition *) (data + 0x1be);
	for (slot = 1; slot <= 4; slot++, p++) {
		if (p->boot_ind != 0 && p->boot_ind != 0x80) {
			/*
			 * Even without a valid boot inidicator value
			 * its still possible this is valid FAT filesystem
			 * without a partition table.
			 */
			fb = (struct fat_boot_sector *) data;
			if (slot == 1 && fb->reserved && fb->fats
				&& fat_valid_media(fb->media)) {
				printk("\n");
				put_dev_sector(sect);
				return 1;
			} else {
				put_dev_sector(sect);
				return 0;
			}
		}
	}

#ifdef CONFIG_EFI_PARTITION
	p = (struct partition *) (data + 0x1be);
	for (slot = 1 ; slot <= 4 ; slot++, p++) {
		/* If this is an EFI GPT disk, msdos should ignore it. */
		if (SYS_IND(p) == EFI_PMBR_OSTYPE_EFI_GPT) {
			put_dev_sector(sect);
			return 0;
		}
	}
#endif
	p = (struct partition *) (data + 0x1be);

	/*
	 * Look for partitions in two passes:
	 * First find the primary and DOS-type extended partitions.
	 * On the second pass look inside *BSD, Unixware and Solaris partitions.
	 */

	state->next = 5;
	for (slot = 1 ; slot <= 4 ; slot++, p++) {
		sector_t start = start_sect(p)*sector_size;
		sector_t size = nr_sects(p)*sector_size;
		if (!size)
			continue;
		if (is_extended_partition(p)) {
			/*
			 * prevent someone doing mkfs or mkswap on an
			 * extended partition, but leave room for LILO
			 * FIXME: this uses one logical sector for > 512b
			 * sector, although it may not be enough/proper.
			 */
			sector_t n = 2;
			n = min(size, max(sector_size, n));
			put_partition(state, slot, start, n);

			printk(" <");
			parse_extended(state, bdev, start, size);
			printk(" >");
			continue;
		}
		put_partition(state, slot, start, size);
		if (SYS_IND(p) == LINUX_RAID_PARTITION)
			state->parts[slot].flags = 1;
		if (SYS_IND(p) == DM6_PARTITION)
			printk("[DM]");
		if (SYS_IND(p) == EZD_PARTITION)
			printk("[EZD]");
	}

	printk("\n");

	/* second pass - output for each on a separate line */
	p = (struct partition *) (0x1be + data);
	for (slot = 1 ; slot <= 4 ; slot++, p++) {
		unsigned char id = SYS_IND(p);
		int n;

		if (!nr_sects(p))
			continue;

		for (n = 0; subtypes[n].parse && id != subtypes[n].id; n++)
			;

		if (!subtypes[n].parse)
			continue;
		subtypes[n].parse(state, bdev, start_sect(p)*sector_size,
						nr_sects(p)*sector_size, slot);
	}
	put_dev_sector(sect);
	return 1;
}