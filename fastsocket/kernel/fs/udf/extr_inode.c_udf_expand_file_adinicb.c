#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct TYPE_4__ {char* i_data; } ;
struct udf_inode_info {int i_lenAlloc; int i_lenEAttr; void* i_alloc_type; TYPE_1__ i_ext; } ;
struct page {int dummy; } ;
struct TYPE_5__ {TYPE_3__* a_ops; } ;
struct inode {TYPE_2__ i_data; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* writepage ) (struct page*,struct writeback_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* ICBTAG_FLAG_AD_LONG ; 
 void* ICBTAG_FLAG_AD_SHORT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  UDF_FLAG_USE_SHORT_AD ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 scalar_t__ UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 struct page* grab_cache_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct page*,struct writeback_control*) ; 
 TYPE_3__ udf_aops ; 

void udf_expand_file_adinicb(struct inode *inode, int newsize, int *err)
{
	struct page *page;
	char *kaddr;
	struct udf_inode_info *iinfo = UDF_I(inode);
	struct writeback_control udf_wbc = {
		.sync_mode = WB_SYNC_NONE,
		.nr_to_write = 1,
	};

	/* from now on we have normal address_space methods */
	inode->i_data.a_ops = &udf_aops;

	if (!iinfo->i_lenAlloc) {
		if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
		else
			iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
		mark_inode_dirty(inode);
		return;
	}

	page = grab_cache_page(inode->i_mapping, 0);
	BUG_ON(!PageLocked(page));

	if (!PageUptodate(page)) {
		kaddr = kmap(page);
		memset(kaddr + iinfo->i_lenAlloc, 0x00,
		       PAGE_CACHE_SIZE - iinfo->i_lenAlloc);
		memcpy(kaddr, iinfo->i_ext.i_data + iinfo->i_lenEAttr,
			iinfo->i_lenAlloc);
		flush_dcache_page(page);
		SetPageUptodate(page);
		kunmap(page);
	}
	memset(iinfo->i_ext.i_data + iinfo->i_lenEAttr, 0x00,
	       iinfo->i_lenAlloc);
	iinfo->i_lenAlloc = 0;
	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
	else
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;

	inode->i_data.a_ops->writepage(page, &udf_wbc);
	page_cache_release(page);

	mark_inode_dirty(inode);
}