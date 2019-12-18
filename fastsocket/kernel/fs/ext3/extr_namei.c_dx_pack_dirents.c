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
struct ext3_dir_entry_2 {int /*<<< orphan*/  rec_len; scalar_t__ name_len; scalar_t__ inode; } ;

/* Variables and functions */
 unsigned int EXT3_DIR_REC_LEN (scalar_t__) ; 
 struct ext3_dir_entry_2* ext3_next_entry (struct ext3_dir_entry_2*) ; 
 int /*<<< orphan*/  ext3_rec_len_to_disk (unsigned int) ; 
 int /*<<< orphan*/  memmove (struct ext3_dir_entry_2*,struct ext3_dir_entry_2*,unsigned int) ; 

__attribute__((used)) static struct ext3_dir_entry_2 *dx_pack_dirents(char *base, unsigned blocksize)
{
	struct ext3_dir_entry_2 *next, *to, *prev;
	struct ext3_dir_entry_2 *de = (struct ext3_dir_entry_2 *)base;
	unsigned rec_len = 0;

	prev = to = de;
	while ((char *)de < base + blocksize) {
		next = ext3_next_entry(de);
		if (de->inode && de->name_len) {
			rec_len = EXT3_DIR_REC_LEN(de->name_len);
			if (de > to)
				memmove(to, de, rec_len);
			to->rec_len = ext3_rec_len_to_disk(rec_len);
			prev = to;
			to = (struct ext3_dir_entry_2 *) (((char *) to) + rec_len);
		}
		de = next;
	}
	return prev;
}