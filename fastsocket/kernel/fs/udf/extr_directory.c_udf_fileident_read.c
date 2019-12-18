#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned char uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/ * i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; scalar_t__ i_efe; TYPE_1__ i_ext; } ;
struct udf_fileident_bh {int soffset; int eoffset; struct buffer_head* ebh; struct buffer_head* sbh; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {TYPE_2__* i_sb; } ;
struct fileIdentDesc {int lengthFileIdent; int /*<<< orphan*/  lengthOfImpUse; } ;
struct fileEntry {int dummy; } ;
struct extent_position {int offset; } ;
struct extendedFileEntry {int dummy; } ;
struct buffer_head {int /*<<< orphan*/ * b_data; } ;
typedef  unsigned char sector_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int s_blocksize; unsigned char s_blocksize_bits; } ;

/* Variables and functions */
 int EXT_RECORDED_ALLOCATED ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 int /*<<< orphan*/  READA ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct fileIdentDesc* udf_get_fileident (int /*<<< orphan*/ *,int,int*) ; 
 int udf_get_lb_pblock (TYPE_2__*,struct kernel_lb_addr*,unsigned char) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,unsigned char*,int) ; 
 struct buffer_head* udf_tgetblk (TYPE_2__*,int) ; 
 void* udf_tread (TYPE_2__*,int) ; 

struct fileIdentDesc *udf_fileident_read(struct inode *dir, loff_t *nf_pos,
					 struct udf_fileident_bh *fibh,
					 struct fileIdentDesc *cfi,
					 struct extent_position *epos,
					 struct kernel_lb_addr *eloc, uint32_t *elen,
					 sector_t *offset)
{
	struct fileIdentDesc *fi;
	int i, num, block;
	struct buffer_head *tmp, *bha[16];
	struct udf_inode_info *iinfo = UDF_I(dir);

	fibh->soffset = fibh->eoffset;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
		fi = udf_get_fileident(iinfo->i_ext.i_data -
				       (iinfo->i_efe ?
					sizeof(struct extendedFileEntry) :
					sizeof(struct fileEntry)),
				       dir->i_sb->s_blocksize,
				       &(fibh->eoffset));
		if (!fi)
			return NULL;

		*nf_pos += fibh->eoffset - fibh->soffset;

		memcpy((uint8_t *)cfi, (uint8_t *)fi,
		       sizeof(struct fileIdentDesc));

		return fi;
	}

	if (fibh->eoffset == dir->i_sb->s_blocksize) {
		int lextoffset = epos->offset;
		unsigned char blocksize_bits = dir->i_sb->s_blocksize_bits;

		if (udf_next_aext(dir, epos, eloc, elen, 1) !=
		    (EXT_RECORDED_ALLOCATED >> 30))
			return NULL;

		block = udf_get_lb_pblock(dir->i_sb, eloc, *offset);

		(*offset)++;

		if ((*offset << blocksize_bits) >= *elen)
			*offset = 0;
		else
			epos->offset = lextoffset;

		brelse(fibh->sbh);
		fibh->sbh = fibh->ebh = udf_tread(dir->i_sb, block);
		if (!fibh->sbh)
			return NULL;
		fibh->soffset = fibh->eoffset = 0;

		if (!(*offset & ((16 >> (blocksize_bits - 9)) - 1))) {
			i = 16 >> (blocksize_bits - 9);
			if (i + *offset > (*elen >> blocksize_bits))
				i = (*elen >> blocksize_bits)-*offset;
			for (num = 0; i > 0; i--) {
				block = udf_get_lb_pblock(dir->i_sb, eloc,
							  *offset + i);
				tmp = udf_tgetblk(dir->i_sb, block);
				if (tmp && !buffer_uptodate(tmp) &&
						!buffer_locked(tmp))
					bha[num++] = tmp;
				else
					brelse(tmp);
			}
			if (num) {
				ll_rw_block(READA, num, bha);
				for (i = 0; i < num; i++)
					brelse(bha[i]);
			}
		}
	} else if (fibh->sbh != fibh->ebh) {
		brelse(fibh->sbh);
		fibh->sbh = fibh->ebh;
	}

	fi = udf_get_fileident(fibh->sbh->b_data, dir->i_sb->s_blocksize,
			       &(fibh->eoffset));

	if (!fi)
		return NULL;

	*nf_pos += fibh->eoffset - fibh->soffset;

	if (fibh->eoffset <= dir->i_sb->s_blocksize) {
		memcpy((uint8_t *)cfi, (uint8_t *)fi,
		       sizeof(struct fileIdentDesc));
	} else if (fibh->eoffset > dir->i_sb->s_blocksize) {
		int lextoffset = epos->offset;

		if (udf_next_aext(dir, epos, eloc, elen, 1) !=
		    (EXT_RECORDED_ALLOCATED >> 30))
			return NULL;

		block = udf_get_lb_pblock(dir->i_sb, eloc, *offset);

		(*offset)++;

		if ((*offset << dir->i_sb->s_blocksize_bits) >= *elen)
			*offset = 0;
		else
			epos->offset = lextoffset;

		fibh->soffset -= dir->i_sb->s_blocksize;
		fibh->eoffset -= dir->i_sb->s_blocksize;

		fibh->ebh = udf_tread(dir->i_sb, block);
		if (!fibh->ebh)
			return NULL;

		if (sizeof(struct fileIdentDesc) > -fibh->soffset) {
			int fi_len;

			memcpy((uint8_t *)cfi, (uint8_t *)fi, -fibh->soffset);
			memcpy((uint8_t *)cfi - fibh->soffset,
			       fibh->ebh->b_data,
			       sizeof(struct fileIdentDesc) + fibh->soffset);

			fi_len = (sizeof(struct fileIdentDesc) +
				  cfi->lengthFileIdent +
				  le16_to_cpu(cfi->lengthOfImpUse) + 3) & ~3;

			*nf_pos += fi_len - (fibh->eoffset - fibh->soffset);
			fibh->eoffset = fibh->soffset + fi_len;
		} else {
			memcpy((uint8_t *)cfi, (uint8_t *)fi,
			       sizeof(struct fileIdentDesc));
		}
	}
	return fi;
}