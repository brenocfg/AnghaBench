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
typedef  int ulong ;
typedef  int u32 ;
struct rootsector {struct partition_info* icdpart; struct partition_info* part; } ;
struct partition_info {int flg; int /*<<< orphan*/  siz; int /*<<< orphan*/  st; int /*<<< orphan*/  id; } ;
struct parsed_partitions {int limit; } ;
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int i_size; } ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 scalar_t__ OK_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_PARTITION (struct partition_info*,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int,int,int) ; 
 scalar_t__ read_dev_sector (struct block_device*,int,int /*<<< orphan*/ *) ; 

int atari_partition(struct parsed_partitions *state, struct block_device *bdev)
{
	Sector sect;
	struct rootsector *rs;
	struct partition_info *pi;
	u32 extensect;
	u32 hd_size;
	int slot;
#ifdef ICD_PARTS
	int part_fmt = 0; /* 0:unknown, 1:AHDI, 2:ICD/Supra */
#endif

	rs = (struct rootsector *) read_dev_sector(bdev, 0, &sect);
	if (!rs)
		return -1;

	/* Verify this is an Atari rootsector: */
	hd_size = bdev->bd_inode->i_size >> 9;
	if (!VALID_PARTITION(&rs->part[0], hd_size) &&
	    !VALID_PARTITION(&rs->part[1], hd_size) &&
	    !VALID_PARTITION(&rs->part[2], hd_size) &&
	    !VALID_PARTITION(&rs->part[3], hd_size)) {
		/*
		 * if there's no valid primary partition, assume that no Atari
		 * format partition table (there's no reliable magic or the like
	         * :-()
		 */
		put_dev_sector(sect);
		return 0;
	}

	pi = &rs->part[0];
	printk (" AHDI");
	for (slot = 1; pi < &rs->part[4] && slot < state->limit; slot++, pi++) {
		struct rootsector *xrs;
		Sector sect2;
		ulong partsect;

		if ( !(pi->flg & 1) )
			continue;
		/* active partition */
		if (memcmp (pi->id, "XGM", 3) != 0) {
			/* we don't care about other id's */
			put_partition (state, slot, be32_to_cpu(pi->st),
					be32_to_cpu(pi->siz));
			continue;
		}
		/* extension partition */
#ifdef ICD_PARTS
		part_fmt = 1;
#endif
		printk(" XGM<");
		partsect = extensect = be32_to_cpu(pi->st);
		while (1) {
			xrs = (struct rootsector *)read_dev_sector(bdev, partsect, &sect2);
			if (!xrs) {
				printk (" block %ld read failed\n", partsect);
				put_dev_sector(sect);
				return -1;
			}

			/* ++roman: sanity check: bit 0 of flg field must be set */
			if (!(xrs->part[0].flg & 1)) {
				printk( "\nFirst sub-partition in extended partition is not valid!\n" );
				put_dev_sector(sect2);
				break;
			}

			put_partition(state, slot,
				   partsect + be32_to_cpu(xrs->part[0].st),
				   be32_to_cpu(xrs->part[0].siz));

			if (!(xrs->part[1].flg & 1)) {
				/* end of linked partition list */
				put_dev_sector(sect2);
				break;
			}
			if (memcmp( xrs->part[1].id, "XGM", 3 ) != 0) {
				printk("\nID of extended partition is not XGM!\n");
				put_dev_sector(sect2);
				break;
			}

			partsect = be32_to_cpu(xrs->part[1].st) + extensect;
			put_dev_sector(sect2);
			if (++slot == state->limit) {
				printk( "\nMaximum number of partitions reached!\n" );
				break;
			}
		}
		printk(" >");
	}
#ifdef ICD_PARTS
	if ( part_fmt!=1 ) { /* no extended partitions -> test ICD-format */
		pi = &rs->icdpart[0];
		/* sanity check: no ICD format if first partition invalid */
		if (OK_id(pi->id)) {
			printk(" ICD<");
			for (; pi < &rs->icdpart[8] && slot < state->limit; slot++, pi++) {
				/* accept only GEM,BGM,RAW,LNX,SWP partitions */
				if (!((pi->flg & 1) && OK_id(pi->id)))
					continue;
				part_fmt = 2;
				put_partition (state, slot,
						be32_to_cpu(pi->st),
						be32_to_cpu(pi->siz));
			}
			printk(" >");
		}
	}
#endif
	put_dev_sector(sect);

	printk ("\n");

	return 1;
}