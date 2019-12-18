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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  QNX4DEBUG (char*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long qnx4_block_map (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qnx4_get_block( struct inode *inode, sector_t iblock, struct buffer_head *bh, int create )
{
	unsigned long phys;

	QNX4DEBUG(("qnx4: qnx4_get_block inode=[%ld] iblock=[%ld]\n",inode->i_ino,iblock));

	phys = qnx4_block_map( inode, iblock );
	if ( phys ) {
		// logical block is before EOF
		map_bh(bh, inode->i_sb, phys);
	} else if ( create ) {
		// to be done.
	}
	return 0;
}