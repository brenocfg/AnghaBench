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
struct TYPE_2__ {scalar_t__ bi_level; int /*<<< orphan*/  bi_blkoff; } ;
union nilfs_binfo {TYPE_1__ bi_dat; } ;
struct nilfs_direct {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_bmap_key_to_dkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_direct_set_ptr (struct nilfs_direct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_direct_assign_p(struct nilfs_direct *direct,
				 __u64 key, __u64 ptr,
				 struct buffer_head **bh,
				 sector_t blocknr,
				 union nilfs_binfo *binfo)
{
	nilfs_direct_set_ptr(direct, key, blocknr);

	binfo->bi_dat.bi_blkoff = nilfs_bmap_key_to_dkey(key);
	binfo->bi_dat.bi_level = 0;

	return 0;
}