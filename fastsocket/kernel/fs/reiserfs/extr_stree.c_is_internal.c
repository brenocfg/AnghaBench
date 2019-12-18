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
struct buffer_head {int dummy; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 int BLKH_SIZE ; 
 int DC_SIZE ; 
 int DISK_LEAF_NODE_LEVEL ; 
 int KEY_SIZE ; 
 int MAX_HEIGHT ; 
 int blkh_free_space (struct block_head*) ; 
 int blkh_level (struct block_head*) ; 
 int blkh_nr_item (struct block_head*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,char*,...) ; 

__attribute__((used)) static int is_internal(char *buf, int blocksize, struct buffer_head *bh)
{
	struct block_head *blkh;
	int nr;
	int used_space;

	blkh = (struct block_head *)buf;
	nr = blkh_level(blkh);
	if (nr <= DISK_LEAF_NODE_LEVEL || nr > MAX_HEIGHT) {
		/* this level is not possible for internal nodes */
		reiserfs_warning(NULL, "reiserfs-5087",
				 "this should be caught earlier");
		return 0;
	}

	nr = blkh_nr_item(blkh);
	if (nr > (blocksize - BLKH_SIZE - DC_SIZE) / (KEY_SIZE + DC_SIZE)) {
		/* for internal which is not root we might check min number of keys */
		reiserfs_warning(NULL, "reiserfs-5088",
				 "number of key seems wrong: %z", bh);
		return 0;
	}

	used_space = BLKH_SIZE + KEY_SIZE * nr + DC_SIZE * (nr + 1);
	if (used_space != blocksize - blkh_free_space(blkh)) {
		reiserfs_warning(NULL, "reiserfs-5089",
				 "free space seems wrong: %z", bh);
		return 0;
	}
	// one may imagine much more checks
	return 1;
}