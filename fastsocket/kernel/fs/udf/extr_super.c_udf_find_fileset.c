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
typedef  int uint16_t ;
struct udf_sb_info {int s_partitions; int s_partition; TYPE_1__* s_partmaps; } ;
struct super_block {int s_blocksize_bits; } ;
struct spaceBitmapDesc {int /*<<< orphan*/  numOfBytes; } ;
struct kernel_lb_addr {int logicalBlockNum; int partitionReferenceNum; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {long s_partition_len; } ;

/* Variables and functions */
#define  TAG_IDENT_FSD 129 
#define  TAG_IDENT_SBD 128 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,int,int) ; 
 int /*<<< orphan*/  udf_load_fileset (struct super_block*,struct buffer_head*,struct kernel_lb_addr*) ; 
 struct buffer_head* udf_read_ptagged (struct super_block*,struct kernel_lb_addr*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int udf_find_fileset(struct super_block *sb,
			    struct kernel_lb_addr *fileset,
			    struct kernel_lb_addr *root)
{
	struct buffer_head *bh = NULL;
	long lastblock;
	uint16_t ident;
	struct udf_sb_info *sbi;

	if (fileset->logicalBlockNum != 0xFFFFFFFF ||
	    fileset->partitionReferenceNum != 0xFFFF) {
		bh = udf_read_ptagged(sb, fileset, 0, &ident);

		if (!bh) {
			return 1;
		} else if (ident != TAG_IDENT_FSD) {
			brelse(bh);
			return 1;
		}

	}

	sbi = UDF_SB(sb);
	if (!bh) {
		/* Search backwards through the partitions */
		struct kernel_lb_addr newfileset;

/* --> cvg: FIXME - is it reasonable? */
		return 1;

		for (newfileset.partitionReferenceNum = sbi->s_partitions - 1;
		     (newfileset.partitionReferenceNum != 0xFFFF &&
		      fileset->logicalBlockNum == 0xFFFFFFFF &&
		      fileset->partitionReferenceNum == 0xFFFF);
		     newfileset.partitionReferenceNum--) {
			lastblock = sbi->s_partmaps
					[newfileset.partitionReferenceNum]
						.s_partition_len;
			newfileset.logicalBlockNum = 0;

			do {
				bh = udf_read_ptagged(sb, &newfileset, 0,
						      &ident);
				if (!bh) {
					newfileset.logicalBlockNum++;
					continue;
				}

				switch (ident) {
				case TAG_IDENT_SBD:
				{
					struct spaceBitmapDesc *sp;
					sp = (struct spaceBitmapDesc *)
								bh->b_data;
					newfileset.logicalBlockNum += 1 +
						((le32_to_cpu(sp->numOfBytes) +
						  sizeof(struct spaceBitmapDesc)
						  - 1) >> sb->s_blocksize_bits);
					brelse(bh);
					break;
				}
				case TAG_IDENT_FSD:
					*fileset = newfileset;
					break;
				default:
					newfileset.logicalBlockNum++;
					brelse(bh);
					bh = NULL;
					break;
				}
			} while (newfileset.logicalBlockNum < lastblock &&
				 fileset->logicalBlockNum == 0xFFFFFFFF &&
				 fileset->partitionReferenceNum == 0xFFFF);
		}
	}

	if ((fileset->logicalBlockNum != 0xFFFFFFFF ||
	     fileset->partitionReferenceNum != 0xFFFF) && bh) {
		udf_debug("Fileset at block=%d, partition=%d\n",
			  fileset->logicalBlockNum,
			  fileset->partitionReferenceNum);

		sbi->s_partition = fileset->partitionReferenceNum;
		udf_load_fileset(sb, bh, root);
		brelse(bh);
		return 0;
	}
	return 1;
}