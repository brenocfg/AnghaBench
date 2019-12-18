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
typedef  scalar_t__ u32 ;
struct inode {TYPE_1__* i_sb; } ;
struct ext3_dir_entry_2 {void* rec_len; } ;
struct dx_map_entry {int size; scalar_t__ hash; } ;
struct dx_hash_info {scalar_t__ hash; } ;
struct dx_frame {int /*<<< orphan*/  entries; struct buffer_head* bh; int /*<<< orphan*/  at; } ;
struct buffer_head {char* b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dx_get_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dx_insert_block (struct dx_frame*,scalar_t__,scalar_t__) ; 
 unsigned int dx_make_map (struct ext3_dir_entry_2*,unsigned int,struct dx_hash_info*,struct dx_map_entry*) ; 
 struct ext3_dir_entry_2* dx_move_dirents (char*,char*,struct dx_map_entry*,unsigned int) ; 
 struct ext3_dir_entry_2* dx_pack_dirents (char*,unsigned int) ; 
 int /*<<< orphan*/  dx_show_index (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dx_show_leaf (struct dx_hash_info*,struct ext3_dir_entry_2*,unsigned int,int) ; 
 int /*<<< orphan*/  dx_sort_map (struct dx_map_entry*,unsigned int) ; 
 int /*<<< orphan*/  dxtrace (int /*<<< orphan*/ ) ; 
 struct buffer_head* ext3_append (int /*<<< orphan*/ *,struct inode*,scalar_t__*,int*) ; 
 int ext3_journal_dirty_metadata (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext3_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 void* ext3_rec_len_to_disk (int) ; 
 int /*<<< orphan*/  ext3_std_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  swap (struct buffer_head*,struct buffer_head*) ; 

__attribute__((used)) static struct ext3_dir_entry_2 *do_split(handle_t *handle, struct inode *dir,
			struct buffer_head **bh,struct dx_frame *frame,
			struct dx_hash_info *hinfo, int *error)
{
	unsigned blocksize = dir->i_sb->s_blocksize;
	unsigned count, continued;
	struct buffer_head *bh2;
	u32 newblock;
	u32 hash2;
	struct dx_map_entry *map;
	char *data1 = (*bh)->b_data, *data2;
	unsigned split, move, size;
	struct ext3_dir_entry_2 *de = NULL, *de2;
	int	err = 0, i;

	bh2 = ext3_append (handle, dir, &newblock, &err);
	if (!(bh2)) {
		brelse(*bh);
		*bh = NULL;
		goto errout;
	}

	BUFFER_TRACE(*bh, "get_write_access");
	err = ext3_journal_get_write_access(handle, *bh);
	if (err)
		goto journal_error;

	BUFFER_TRACE(frame->bh, "get_write_access");
	err = ext3_journal_get_write_access(handle, frame->bh);
	if (err)
		goto journal_error;

	data2 = bh2->b_data;

	/* create map in the end of data2 block */
	map = (struct dx_map_entry *) (data2 + blocksize);
	count = dx_make_map ((struct ext3_dir_entry_2 *) data1,
			     blocksize, hinfo, map);
	map -= count;
	dx_sort_map (map, count);
	/* Split the existing block in the middle, size-wise */
	size = 0;
	move = 0;
	for (i = count-1; i >= 0; i--) {
		/* is more than half of this entry in 2nd half of the block? */
		if (size + map[i].size/2 > blocksize/2)
			break;
		size += map[i].size;
		move++;
	}
	/* map index at which we will split */
	split = count - move;
	hash2 = map[split].hash;
	continued = hash2 == map[split - 1].hash;
	dxtrace(printk("Split block %i at %x, %i/%i\n",
		dx_get_block(frame->at), hash2, split, count-split));

	/* Fancy dance to stay within two buffers */
	de2 = dx_move_dirents(data1, data2, map + split, count - split);
	de = dx_pack_dirents(data1,blocksize);
	de->rec_len = ext3_rec_len_to_disk(data1 + blocksize - (char *) de);
	de2->rec_len = ext3_rec_len_to_disk(data2 + blocksize - (char *) de2);
	dxtrace(dx_show_leaf (hinfo, (struct ext3_dir_entry_2 *) data1, blocksize, 1));
	dxtrace(dx_show_leaf (hinfo, (struct ext3_dir_entry_2 *) data2, blocksize, 1));

	/* Which block gets the new entry? */
	if (hinfo->hash >= hash2)
	{
		swap(*bh, bh2);
		de = de2;
	}
	dx_insert_block (frame, hash2 + continued, newblock);
	err = ext3_journal_dirty_metadata (handle, bh2);
	if (err)
		goto journal_error;
	err = ext3_journal_dirty_metadata (handle, frame->bh);
	if (err)
		goto journal_error;
	brelse (bh2);
	dxtrace(dx_show_index ("frame", frame->entries));
	return de;

journal_error:
	brelse(*bh);
	brelse(bh2);
	*bh = NULL;
	ext3_std_error(dir->i_sb, err);
errout:
	*error = err;
	return NULL;
}