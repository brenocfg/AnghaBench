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
typedef  int u64 ;
struct super_block {int s_blocksize; } ;
struct omfs_sb_info {int s_imap_size; int /*<<< orphan*/  s_bitmap_lock; int /*<<< orphan*/ * s_imap; } ;

/* Variables and functions */
 int ENOSPC ; 
 struct omfs_sb_info* OMFS_SB (struct super_block*) ; 
 int count_run (int /*<<< orphan*/ *,int,int,int,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_run (struct super_block*,int,int,int,int,int) ; 

int omfs_allocate_range(struct super_block *sb,
			int min_request,
			int max_request,
			u64 *return_block,
			int *return_size)
{
	struct omfs_sb_info *sbi = OMFS_SB(sb);
	int bits_per_entry = 8 * sb->s_blocksize;
	int ret = 0;
	int i, run, bit;

	mutex_lock(&sbi->s_bitmap_lock);
	for (i = 0; i < sbi->s_imap_size; i++) {
		bit = 0;
		while (bit < bits_per_entry) {
			bit = find_next_zero_bit(sbi->s_imap[i], bits_per_entry,
				bit);

			if (bit == bits_per_entry)
				break;

			run = count_run(&sbi->s_imap[i], bits_per_entry,
				sbi->s_imap_size-i, bit, max_request);

			if (run >= min_request)
				goto found;
			bit += run;
		}
	}
	ret = -ENOSPC;
	goto out;

found:
	*return_block = i * bits_per_entry + bit;
	*return_size = run;
	ret = set_run(sb, i, bits_per_entry, bit, run, 1);

out:
	mutex_unlock(&sbi->s_bitmap_lock);
	return ret;
}