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
struct nilfs_palloc_req {void* pr_entry_nr; } ;
struct nilfs_direct {int dummy; } ;
struct nilfs_bmap {scalar_t__ b_ptr_type; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  void* __u64 ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_PTR_VS ; 
 int /*<<< orphan*/  NILFS_BMAP_USE_VBN (struct nilfs_bmap const*) ; 
 int /*<<< orphan*/  buffer_nilfs_volatile (struct buffer_head*) ; 
 void* nilfs_bmap_data_get_key (struct nilfs_bmap const*,struct buffer_head*) ; 
 struct inode* nilfs_bmap_get_dat (struct nilfs_bmap const*) ; 
 int /*<<< orphan*/  nilfs_dat_commit_update (struct inode*,struct nilfs_palloc_req*,struct nilfs_palloc_req*,int) ; 
 int nilfs_dat_mark_dirty (struct inode*,void*) ; 
 int nilfs_dat_prepare_update (struct inode*,struct nilfs_palloc_req*,struct nilfs_palloc_req*) ; 
 void* nilfs_direct_get_ptr (struct nilfs_direct*,void*) ; 
 int /*<<< orphan*/  nilfs_direct_set_ptr (struct nilfs_direct*,void*,void*) ; 
 int /*<<< orphan*/  set_buffer_nilfs_volatile (struct buffer_head*) ; 

__attribute__((used)) static int nilfs_direct_propagate(const struct nilfs_bmap *bmap,
				  struct buffer_head *bh)
{
	struct nilfs_direct *direct = (struct nilfs_direct *)bmap;
	struct nilfs_palloc_req oldreq, newreq;
	struct inode *dat;
	__u64 key;
	__u64 ptr;
	int ret;

	if (!NILFS_BMAP_USE_VBN(bmap))
		return 0;

	dat = nilfs_bmap_get_dat(bmap);
	key = nilfs_bmap_data_get_key(bmap, bh);
	ptr = nilfs_direct_get_ptr(direct, key);
	if (!buffer_nilfs_volatile(bh)) {
		oldreq.pr_entry_nr = ptr;
		newreq.pr_entry_nr = ptr;
		ret = nilfs_dat_prepare_update(dat, &oldreq, &newreq);
		if (ret < 0)
			return ret;
		nilfs_dat_commit_update(dat, &oldreq, &newreq,
					bmap->b_ptr_type == NILFS_BMAP_PTR_VS);
		set_buffer_nilfs_volatile(bh);
		nilfs_direct_set_ptr(direct, key, newreq.pr_entry_nr);
	} else
		ret = nilfs_dat_mark_dirty(dat, ptr);

	return ret;
}