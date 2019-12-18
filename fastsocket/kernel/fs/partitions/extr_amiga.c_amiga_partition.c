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
struct parsed_partitions {int dummy; } ;
struct block_device {int dummy; } ;
struct RigidDiskBlock {scalar_t__ rdb_SummedLongs; scalar_t__ rdb_BlockBytes; scalar_t__ rdb_PartitionList; } ;
struct PartitionBlock {scalar_t__ pb_Next; scalar_t__ pb_ID; scalar_t__ pb_SummedLongs; scalar_t__* pb_Environment; } ;
typedef  scalar_t__ __be32 ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  IDNAME_PARTITION ; 
 int /*<<< orphan*/  IDNAME_RIGIDDISK ; 
 int RDB_ALLOCATION_LIMIT ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 int be32_to_cpu (scalar_t__) ; 
 scalar_t__ checksum_block (scalar_t__*,int) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_partition (struct parsed_partitions*,int /*<<< orphan*/ ,int,int) ; 
 unsigned char* read_dev_sector (struct block_device*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ warn_no_part ; 

int
amiga_partition(struct parsed_partitions *state, struct block_device *bdev)
{
	Sector sect;
	unsigned char *data;
	struct RigidDiskBlock *rdb;
	struct PartitionBlock *pb;
	int start_sect, nr_sects, blk, part, res = 0;
	int blksize = 1;	/* Multiplier for disk block size */
	int slot = 1;
	char b[BDEVNAME_SIZE];

	for (blk = 0; ; blk++, put_dev_sector(sect)) {
		if (blk == RDB_ALLOCATION_LIMIT)
			goto rdb_done;
		data = read_dev_sector(bdev, blk, &sect);
		if (!data) {
			if (warn_no_part)
				printk("Dev %s: unable to read RDB block %d\n",
				       bdevname(bdev, b), blk);
			res = -1;
			goto rdb_done;
		}
		if (*(__be32 *)data != cpu_to_be32(IDNAME_RIGIDDISK))
			continue;

		rdb = (struct RigidDiskBlock *)data;
		if (checksum_block((__be32 *)data, be32_to_cpu(rdb->rdb_SummedLongs) & 0x7F) == 0)
			break;
		/* Try again with 0xdc..0xdf zeroed, Windows might have
		 * trashed it.
		 */
		*(__be32 *)(data+0xdc) = 0;
		if (checksum_block((__be32 *)data,
				be32_to_cpu(rdb->rdb_SummedLongs) & 0x7F)==0) {
			printk("Warning: Trashed word at 0xd0 in block %d "
				"ignored in checksum calculation\n",blk);
			break;
		}

		printk("Dev %s: RDB in block %d has bad checksum\n",
			       bdevname(bdev, b), blk);
	}

	/* blksize is blocks per 512 byte standard block */
	blksize = be32_to_cpu( rdb->rdb_BlockBytes ) / 512;

	printk(" RDSK (%d)", blksize * 512);	/* Be more informative */
	blk = be32_to_cpu(rdb->rdb_PartitionList);
	put_dev_sector(sect);
	for (part = 1; blk>0 && part<=16; part++, put_dev_sector(sect)) {
		blk *= blksize;	/* Read in terms partition table understands */
		data = read_dev_sector(bdev, blk, &sect);
		if (!data) {
			if (warn_no_part)
				printk("Dev %s: unable to read partition block %d\n",
				       bdevname(bdev, b), blk);
			res = -1;
			goto rdb_done;
		}
		pb  = (struct PartitionBlock *)data;
		blk = be32_to_cpu(pb->pb_Next);
		if (pb->pb_ID != cpu_to_be32(IDNAME_PARTITION))
			continue;
		if (checksum_block((__be32 *)pb, be32_to_cpu(pb->pb_SummedLongs) & 0x7F) != 0 )
			continue;

		/* Tell Kernel about it */

		nr_sects = (be32_to_cpu(pb->pb_Environment[10]) + 1 -
			    be32_to_cpu(pb->pb_Environment[9])) *
			   be32_to_cpu(pb->pb_Environment[3]) *
			   be32_to_cpu(pb->pb_Environment[5]) *
			   blksize;
		if (!nr_sects)
			continue;
		start_sect = be32_to_cpu(pb->pb_Environment[9]) *
			     be32_to_cpu(pb->pb_Environment[3]) *
			     be32_to_cpu(pb->pb_Environment[5]) *
			     blksize;
		put_partition(state,slot++,start_sect,nr_sects);
		{
			/* Be even more informative to aid mounting */
			char dostype[4];
			__be32 *dt = (__be32 *)dostype;
			*dt = pb->pb_Environment[16];
			if (dostype[3] < ' ')
				printk(" (%c%c%c^%c)",
					dostype[0], dostype[1],
					dostype[2], dostype[3] + '@' );
			else
				printk(" (%c%c%c%c)",
					dostype[0], dostype[1],
					dostype[2], dostype[3]);
			printk("(res %d spb %d)",
				be32_to_cpu(pb->pb_Environment[6]),
				be32_to_cpu(pb->pb_Environment[4]));
		}
		res = 1;
	}
	printk("\n");

rdb_done:
	return res;
}