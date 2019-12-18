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
struct inode {int dummy; } ;
struct ext4_ext_cache {scalar_t__ ec_len; int /*<<< orphan*/  ec_start; int /*<<< orphan*/  ec_block; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_block_reservation_lock; struct ext4_ext_cache i_cached_extent; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  ext_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ in_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct ext4_ext_cache*,struct ext4_ext_cache*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_ext_check_cache(struct inode *inode, ext4_lblk_t block,
	struct ext4_ext_cache *ex){
	struct ext4_ext_cache *cex;
	int ret = 0;

	/* 
	 * We borrow i_block_reservation_lock to protect i_cached_extent
	 */
	spin_lock(&EXT4_I(inode)->i_block_reservation_lock);
	cex = &EXT4_I(inode)->i_cached_extent;

	/* has cache valid data? */
	if (cex->ec_len == 0)
		goto errout;

	if (in_range(block, cex->ec_block, cex->ec_len)) {
		memcpy(ex, cex, sizeof(struct ext4_ext_cache));
		ext_debug("%u cached by %u:%u:%llu\n",
				block,
				cex->ec_block, cex->ec_len, cex->ec_start);
		ret = 1;
	}
errout:
	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);
	return ret;
}