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
struct volStructDesc {scalar_t__* stdIdent; int structType; } ;
struct udf_sb_info {int s_session; } ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  VSD_STD_ID_BEA01 ; 
 int /*<<< orphan*/  VSD_STD_ID_CD001 ; 
 int /*<<< orphan*/  VSD_STD_ID_LEN ; 
 int /*<<< orphan*/  VSD_STD_ID_NSR02 ; 
 int /*<<< orphan*/  VSD_STD_ID_NSR03 ; 
 int /*<<< orphan*/  VSD_STD_ID_TEA01 ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,...) ; 
 struct buffer_head* udf_tread (struct super_block*,int) ; 

__attribute__((used)) static loff_t udf_check_vsd(struct super_block *sb)
{
	struct volStructDesc *vsd = NULL;
	loff_t sector = 32768;
	int sectorsize;
	struct buffer_head *bh = NULL;
	int nsr02 = 0;
	int nsr03 = 0;
	struct udf_sb_info *sbi;

	sbi = UDF_SB(sb);
	if (sb->s_blocksize < sizeof(struct volStructDesc))
		sectorsize = sizeof(struct volStructDesc);
	else
		sectorsize = sb->s_blocksize;

	sector += (sbi->s_session << sb->s_blocksize_bits);

	udf_debug("Starting at sector %u (%ld byte sectors)\n",
		  (unsigned int)(sector >> sb->s_blocksize_bits),
		  sb->s_blocksize);
	/* Process the sequence (if applicable) */
	for (; !nsr02 && !nsr03; sector += sectorsize) {
		/* Read a block */
		bh = udf_tread(sb, sector >> sb->s_blocksize_bits);
		if (!bh)
			break;

		/* Look for ISO  descriptors */
		vsd = (struct volStructDesc *)(bh->b_data +
					      (sector & (sb->s_blocksize - 1)));

		if (vsd->stdIdent[0] == 0) {
			brelse(bh);
			break;
		} else if (!strncmp(vsd->stdIdent, VSD_STD_ID_CD001,
				    VSD_STD_ID_LEN)) {
			switch (vsd->structType) {
			case 0:
				udf_debug("ISO9660 Boot Record found\n");
				break;
			case 1:
				udf_debug("ISO9660 Primary Volume Descriptor "
					  "found\n");
				break;
			case 2:
				udf_debug("ISO9660 Supplementary Volume "
					  "Descriptor found\n");
				break;
			case 3:
				udf_debug("ISO9660 Volume Partition Descriptor "
					  "found\n");
				break;
			case 255:
				udf_debug("ISO9660 Volume Descriptor Set "
					  "Terminator found\n");
				break;
			default:
				udf_debug("ISO9660 VRS (%u) found\n",
					  vsd->structType);
				break;
			}
		} else if (!strncmp(vsd->stdIdent, VSD_STD_ID_BEA01,
				    VSD_STD_ID_LEN))
			; /* nothing */
		else if (!strncmp(vsd->stdIdent, VSD_STD_ID_TEA01,
				    VSD_STD_ID_LEN)) {
			brelse(bh);
			break;
		} else if (!strncmp(vsd->stdIdent, VSD_STD_ID_NSR02,
				    VSD_STD_ID_LEN))
			nsr02 = sector;
		else if (!strncmp(vsd->stdIdent, VSD_STD_ID_NSR03,
				    VSD_STD_ID_LEN))
			nsr03 = sector;
		brelse(bh);
	}

	if (nsr03)
		return nsr03;
	else if (nsr02)
		return nsr02;
	else if (sector - (sbi->s_session << sb->s_blocksize_bits) == 32768)
		return -1;
	else
		return 0;
}