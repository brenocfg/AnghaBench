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
struct partition {int dummy; } ;
struct parsed_partitions {scalar_t__ next; scalar_t__ limit; int /*<<< orphan*/  name; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int MINIX_NR_SUBPARTITIONS ; 
 scalar_t__ MINIX_PARTITION ; 
 scalar_t__ SYS_IND (struct partition*) ; 
 scalar_t__ msdos_magic_present (unsigned char*) ; 
 int /*<<< orphan*/  nr_sects (struct partition*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* read_dev_sector (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_sect (struct partition*) ; 

__attribute__((used)) static void
parse_minix(struct parsed_partitions *state, struct block_device *bdev,
		sector_t offset, sector_t size, int origin)
{
#ifdef CONFIG_MINIX_SUBPARTITION
	Sector sect;
	unsigned char *data;
	struct partition *p;
	int i;

	data = read_dev_sector(bdev, offset, &sect);
	if (!data)
		return;

	p = (struct partition *)(data + 0x1be);

	/* The first sector of a Minix partition can have either
	 * a secondary MBR describing its subpartitions, or
	 * the normal boot sector. */
	if (msdos_magic_present (data + 510) &&
	    SYS_IND(p) == MINIX_PARTITION) { /* subpartition table present */

		printk(" %s%d: <minix:", state->name, origin);
		for (i = 0; i < MINIX_NR_SUBPARTITIONS; i++, p++) {
			if (state->next == state->limit)
				break;
			/* add each partition in use */
			if (SYS_IND(p) == MINIX_PARTITION)
				put_partition(state, state->next++,
					      start_sect(p), nr_sects(p));
		}
		printk(" >\n");
	}
	put_dev_sector(sect);
#endif /* CONFIG_MINIX_SUBPARTITION */
}