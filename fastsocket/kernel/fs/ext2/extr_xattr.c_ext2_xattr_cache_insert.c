#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mb_cache_entry {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_5__ {int /*<<< orphan*/  h_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  c_entry_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 TYPE_3__* HDR (struct buffer_head*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int,...) ; 
 TYPE_1__* ext2_xattr_cache ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mb_cache_entry* mb_cache_entry_alloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_cache_entry_free (struct mb_cache_entry*) ; 
 int mb_cache_entry_insert (struct mb_cache_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mb_cache_entry_release (struct mb_cache_entry*) ; 

__attribute__((used)) static int
ext2_xattr_cache_insert(struct buffer_head *bh)
{
	__u32 hash = le32_to_cpu(HDR(bh)->h_hash);
	struct mb_cache_entry *ce;
	int error;

	ce = mb_cache_entry_alloc(ext2_xattr_cache, GFP_NOFS);
	if (!ce)
		return -ENOMEM;
	error = mb_cache_entry_insert(ce, bh->b_bdev, bh->b_blocknr, &hash);
	if (error) {
		mb_cache_entry_free(ce);
		if (error == -EBUSY) {
			ea_bdebug(bh, "already in cache (%d cache entries)",
				atomic_read(&ext2_xattr_cache->c_entry_count));
			error = 0;
		}
	} else {
		ea_bdebug(bh, "inserting [%x] (%d cache entries)", (int)hash,
			  atomic_read(&ext2_xattr_cache->c_entry_count));
		mb_cache_entry_release(ce);
	}
	return error;
}