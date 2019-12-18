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
struct minix_sb_info {int s_zmap_blocks; int s_firstdatazone; int s_nzones; struct buffer_head** s_zmap; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_lock ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int minix_find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 struct minix_sb_info* minix_sb (TYPE_1__*) ; 
 int /*<<< orphan*/  minix_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int minix_new_block(struct inode * inode)
{
	struct minix_sb_info *sbi = minix_sb(inode->i_sb);
	int bits_per_zone = 8 * inode->i_sb->s_blocksize;
	int i;

	for (i = 0; i < sbi->s_zmap_blocks; i++) {
		struct buffer_head *bh = sbi->s_zmap[i];
		int j;

		spin_lock(&bitmap_lock);
		j = minix_find_first_zero_bit(bh->b_data, bits_per_zone);
		if (j < bits_per_zone) {
			minix_set_bit(j, bh->b_data);
			spin_unlock(&bitmap_lock);
			mark_buffer_dirty(bh);
			j += i * bits_per_zone + sbi->s_firstdatazone-1;
			if (j < sbi->s_firstdatazone || j >= sbi->s_nzones)
				break;
			return j;
		}
		spin_unlock(&bitmap_lock);
	}
	return 0;
}