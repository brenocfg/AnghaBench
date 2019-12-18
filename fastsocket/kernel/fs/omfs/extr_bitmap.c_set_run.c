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
struct super_block {int dummy; } ;
struct omfs_sb_info {unsigned long** s_imap; int /*<<< orphan*/  s_bitmap_ino; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct omfs_sb_info* OMFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 scalar_t__ clus_to_blk (struct omfs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* sb_bread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static int set_run(struct super_block *sb, int map,
		int nbits, int bit, int count, int set)
{
	int i;
	int err;
	struct buffer_head *bh;
	struct omfs_sb_info *sbi = OMFS_SB(sb);

 	err = -ENOMEM;
	bh = sb_bread(sb, clus_to_blk(sbi, sbi->s_bitmap_ino) + map);
	if (!bh)
		goto out;

	for (i = 0; i < count; i++, bit++) {
		if (bit >= nbits) {
			bit = 0;
			map++;

			mark_buffer_dirty(bh);
			brelse(bh);
			bh = sb_bread(sb,
				clus_to_blk(sbi, sbi->s_bitmap_ino) + map);
			if (!bh)
				goto out;
		}
		if (set) {
			set_bit(bit, sbi->s_imap[map]);
			set_bit(bit, (unsigned long *)bh->b_data);
		} else {
			clear_bit(bit, sbi->s_imap[map]);
			clear_bit(bit, (unsigned long *)bh->b_data);
		}
	}
	mark_buffer_dirty(bh);
	brelse(bh);
	err = 0;
out:
	return err;
}