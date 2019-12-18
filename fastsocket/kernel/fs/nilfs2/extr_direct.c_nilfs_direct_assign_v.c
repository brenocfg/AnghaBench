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
union nilfs_bmap_ptr_req {int /*<<< orphan*/  bpr_req; int /*<<< orphan*/  bpr_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_blkoff; int /*<<< orphan*/  bi_vblocknr; } ;
union nilfs_binfo {TYPE_1__ bi_v; } ;
struct nilfs_direct {int /*<<< orphan*/  d_bmap; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 struct inode* nilfs_bmap_get_dat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_bmap_key_to_dkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_bmap_ptr_to_dptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_dat_commit_start (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_dat_prepare_start (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_direct_assign_v(struct nilfs_direct *direct,
				 __u64 key, __u64 ptr,
				 struct buffer_head **bh,
				 sector_t blocknr,
				 union nilfs_binfo *binfo)
{
	struct inode *dat = nilfs_bmap_get_dat(&direct->d_bmap);
	union nilfs_bmap_ptr_req req;
	int ret;

	req.bpr_ptr = ptr;
	ret = nilfs_dat_prepare_start(dat, &req.bpr_req);
	if (!ret) {
		nilfs_dat_commit_start(dat, &req.bpr_req, blocknr);
		binfo->bi_v.bi_vblocknr = nilfs_bmap_ptr_to_dptr(ptr);
		binfo->bi_v.bi_blkoff = nilfs_bmap_key_to_dkey(key);
	}
	return ret;
}