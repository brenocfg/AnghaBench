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
struct inode {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_len; int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_cache {int /*<<< orphan*/  ec_len; int /*<<< orphan*/  ec_start; int /*<<< orphan*/  ec_block; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ext4_ext_check_cache (struct inode*,int /*<<< orphan*/ ,struct ext4_ext_cache*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_ext_in_cache(struct inode *inode, ext4_lblk_t block,
			struct ext4_extent *ex)
{
	struct ext4_ext_cache cex;
	int ret = 0;

	ret = ext4_ext_check_cache(inode, block, &cex);
	if (ret) {
		ex->ee_block = cpu_to_le32(cex.ec_block);
		ext4_ext_store_pblock(ex, cex.ec_start);
		ex->ee_len = cpu_to_le16(cex.ec_len);
	}

	return ret;
}