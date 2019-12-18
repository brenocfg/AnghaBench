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
typedef  int u64 ;
struct inode {int i_blocks; } ;
struct TYPE_3__ {int sb_bsize_shift; } ;
struct TYPE_4__ {TYPE_1__ sd_sb; } ;

/* Variables and functions */
 int GFS2_BASIC_BLOCK_SHIFT ; 
 TYPE_2__* GFS2_SB (struct inode const*) ; 

__attribute__((used)) static inline u64 gfs2_get_inode_blocks(const struct inode *inode)
{
	return inode->i_blocks >>
		(GFS2_SB(inode)->sd_sb.sb_bsize_shift - GFS2_BASIC_BLOCK_SHIFT);
}