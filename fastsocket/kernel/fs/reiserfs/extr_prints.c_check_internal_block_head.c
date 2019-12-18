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
struct buffer_head {int b_size; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 int BLKH_SIZE ; 
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 int B_FREE_SPACE (struct buffer_head*) ; 
 scalar_t__ B_LEVEL (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 int DC_SIZE ; 
 scalar_t__ DISK_LEAF_NODE_LEVEL ; 
 int IH_SIZE ; 
 int KEY_SIZE ; 
 scalar_t__ MAX_HEIGHT ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ *,char*,char*,struct buffer_head*) ; 

__attribute__((used)) static void check_internal_block_head(struct buffer_head *bh)
{
	struct block_head *blkh;

	blkh = B_BLK_HEAD(bh);
	if (!(B_LEVEL(bh) > DISK_LEAF_NODE_LEVEL && B_LEVEL(bh) <= MAX_HEIGHT))
		reiserfs_panic(NULL, "vs-6025", "invalid level %z", bh);

	if (B_NR_ITEMS(bh) > (bh->b_size - BLKH_SIZE) / IH_SIZE)
		reiserfs_panic(NULL, "vs-6030", "invalid item number %z", bh);

	if (B_FREE_SPACE(bh) !=
	    bh->b_size - BLKH_SIZE - KEY_SIZE * B_NR_ITEMS(bh) -
	    DC_SIZE * (B_NR_ITEMS(bh) + 1))
		reiserfs_panic(NULL, "vs-6040", "invalid free space %z", bh);

}