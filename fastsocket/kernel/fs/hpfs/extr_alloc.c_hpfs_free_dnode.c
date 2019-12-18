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
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
typedef  int dnode_secno ;
struct TYPE_2__ {int sb_dirband_start; int sb_dirband_size; scalar_t__ sb_chk; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int) ; 
 int /*<<< orphan*/  hpfs_free_sectors (struct super_block*,int,int) ; 
 unsigned int* hpfs_map_dnode_bitmap (struct super_block*,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

void hpfs_free_dnode(struct super_block *s, dnode_secno dno)
{
	if (hpfs_sb(s)->sb_chk) if (dno & 3) {
		hpfs_error(s, "hpfs_free_dnode: dnode %08x not aligned", dno);
		return;
	}
	if (dno < hpfs_sb(s)->sb_dirband_start ||
	    dno >= hpfs_sb(s)->sb_dirband_start + hpfs_sb(s)->sb_dirband_size) {
		hpfs_free_sectors(s, dno, 4);
	} else {
		struct quad_buffer_head qbh;
		unsigned *bmp;
		unsigned ssec = (dno - hpfs_sb(s)->sb_dirband_start) / 4;
		lock_super(s);
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) {
			unlock_super(s);
			return;
		}
		bmp[ssec >> 5] |= 1 << (ssec & 0x1f);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
		unlock_super(s);
	}
}