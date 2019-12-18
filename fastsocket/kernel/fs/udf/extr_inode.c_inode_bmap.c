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
typedef  unsigned char uint32_t ;
struct udf_inode_info {unsigned char i_lenExtents; int /*<<< orphan*/  i_location; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct extent_position {int /*<<< orphan*/ * bh; int /*<<< orphan*/  block; scalar_t__ offset; } ;
typedef  unsigned char sector_t ;
typedef  unsigned char loff_t ;
typedef  int int8_t ;
struct TYPE_2__ {unsigned char s_blocksize_bits; } ;

/* Variables and functions */
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,unsigned char*,int) ; 

int8_t inode_bmap(struct inode *inode, sector_t block,
		  struct extent_position *pos, struct kernel_lb_addr *eloc,
		  uint32_t *elen, sector_t *offset)
{
	unsigned char blocksize_bits = inode->i_sb->s_blocksize_bits;
	loff_t lbcount = 0, bcount =
	    (loff_t) block << blocksize_bits;
	int8_t etype;
	struct udf_inode_info *iinfo;

	iinfo = UDF_I(inode);
	pos->offset = 0;
	pos->block = iinfo->i_location;
	pos->bh = NULL;
	*elen = 0;

	do {
		etype = udf_next_aext(inode, pos, eloc, elen, 1);
		if (etype == -1) {
			*offset = (bcount - lbcount) >> blocksize_bits;
			iinfo->i_lenExtents = lbcount;
			return -1;
		}
		lbcount += *elen;
	} while (lbcount <= bcount);

	*offset = (bcount + *elen - lbcount) >> blocksize_bits;

	return etype;
}