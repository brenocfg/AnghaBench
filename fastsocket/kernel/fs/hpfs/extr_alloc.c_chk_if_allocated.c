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
typedef  int secno ;
struct TYPE_2__ {int sb_dirband_start; int sb_dirband_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,char*,int) ; 
 unsigned int* hpfs_map_bitmap (struct super_block*,int,struct quad_buffer_head*,char*) ; 
 unsigned int* hpfs_map_dnode_bitmap (struct super_block*,struct quad_buffer_head*) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 

__attribute__((used)) static int chk_if_allocated(struct super_block *s, secno sec, char *msg)
{
	struct quad_buffer_head qbh;
	unsigned *bmp;
	if (!(bmp = hpfs_map_bitmap(s, sec >> 14, &qbh, "chk"))) goto fail;
	if ((bmp[(sec & 0x3fff) >> 5] >> (sec & 0x1f)) & 1) {
		hpfs_error(s, "sector '%s' - %08x not allocated in bitmap", msg, sec);
		goto fail1;
	}
	hpfs_brelse4(&qbh);
	if (sec >= hpfs_sb(s)->sb_dirband_start && sec < hpfs_sb(s)->sb_dirband_start + hpfs_sb(s)->sb_dirband_size) {
		unsigned ssec = (sec - hpfs_sb(s)->sb_dirband_start) / 4;
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) goto fail;
		if ((bmp[ssec >> 5] >> (ssec & 0x1f)) & 1) {
			hpfs_error(s, "sector '%s' - %08x not allocated in directory bitmap", msg, sec);
			goto fail1;
		}
		hpfs_brelse4(&qbh);
	}
	return 0;
	fail1:
	hpfs_brelse4(&qbh);
	fail:
	return 1;
}