#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct udf_inode_info {scalar_t__ i_alloc_type; } ;
struct udf_fileident_bh {int soffset; int eoffset; int /*<<< orphan*/ * sbh; int /*<<< orphan*/ * ebh; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int i_size; TYPE_1__* i_sb; } ;
struct fileIdentDesc {int fileCharacteristics; scalar_t__ lengthFileIdent; } ;
struct extent_position {int offset; int /*<<< orphan*/ * bh; } ;
typedef  int sector_t ;
typedef  int loff_t ;
struct TYPE_3__ {int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 int EXT_RECORDED_ALLOCATED ; 
 int FID_FILE_CHAR_DELETED ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int inode_bmap (struct inode*,int,struct extent_position*,struct kernel_lb_addr*,int*,int*) ; 
 int udf_ext0_offset (struct inode*) ; 
 struct fileIdentDesc* udf_fileident_read (struct inode*,int*,struct udf_fileident_bh*,struct fileIdentDesc*,struct extent_position*,struct kernel_lb_addr*,int*,int*) ; 
 int udf_get_lb_pblock (TYPE_1__*,struct kernel_lb_addr*,int) ; 
 int /*<<< orphan*/ * udf_tread (TYPE_1__*,int) ; 

__attribute__((used)) static int empty_dir(struct inode *dir)
{
	struct fileIdentDesc *fi, cfi;
	struct udf_fileident_bh fibh;
	loff_t f_pos;
	loff_t size = udf_ext0_offset(dir) + dir->i_size;
	int block;
	struct kernel_lb_addr eloc;
	uint32_t elen;
	sector_t offset;
	struct extent_position epos = {};
	struct udf_inode_info *dinfo = UDF_I(dir);

	f_pos = udf_ext0_offset(dir);
	fibh.soffset = fibh.eoffset = f_pos & (dir->i_sb->s_blocksize - 1);

	if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		fibh.sbh = fibh.ebh = NULL;
	else if (inode_bmap(dir, f_pos >> dir->i_sb->s_blocksize_bits,
			      &epos, &eloc, &elen, &offset) ==
					(EXT_RECORDED_ALLOCATED >> 30)) {
		block = udf_get_lb_pblock(dir->i_sb, &eloc, offset);
		if ((++offset << dir->i_sb->s_blocksize_bits) < elen) {
			if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= sizeof(struct short_ad);
			else if (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= sizeof(struct long_ad);
		} else
			offset = 0;

		fibh.sbh = fibh.ebh = udf_tread(dir->i_sb, block);
		if (!fibh.sbh) {
			brelse(epos.bh);
			return 0;
		}
	} else {
		brelse(epos.bh);
		return 0;
	}

	while (f_pos < size) {
		fi = udf_fileident_read(dir, &f_pos, &fibh, &cfi, &epos, &eloc,
					&elen, &offset);
		if (!fi) {
			if (fibh.sbh != fibh.ebh)
				brelse(fibh.ebh);
			brelse(fibh.sbh);
			brelse(epos.bh);
			return 0;
		}

		if (cfi.lengthFileIdent &&
		    (cfi.fileCharacteristics & FID_FILE_CHAR_DELETED) == 0) {
			if (fibh.sbh != fibh.ebh)
				brelse(fibh.ebh);
			brelse(fibh.sbh);
			brelse(epos.bh);
			return 0;
		}
	}

	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);
	brelse(epos.bh);

	return 1;
}