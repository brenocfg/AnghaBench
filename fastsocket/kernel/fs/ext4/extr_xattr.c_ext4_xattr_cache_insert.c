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
struct mb_cache_entry {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  h_hash; } ;

/* Variables and functions */
 TYPE_1__* BHDR (struct buffer_head*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,...) ; 
 int /*<<< orphan*/  ext4_xattr_cache ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mb_cache_entry* mb_cache_entry_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_cache_entry_free (struct mb_cache_entry*) ; 
 int mb_cache_entry_insert (struct mb_cache_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mb_cache_entry_release (struct mb_cache_entry*) ; 

__attribute__((used)) static void
ext4_xattr_cache_insert(struct buffer_head *bh)
{
	__u32 hash = le32_to_cpu(BHDR(bh)->h_hash);
	struct mb_cache_entry *ce;
	int error;

	ce = mb_cache_entry_alloc(ext4_xattr_cache, GFP_NOFS);
	if (!ce) {
		ea_bdebug(bh, "out of memory");
		return;
	}
	error = mb_cache_entry_insert(ce, bh->b_bdev, bh->b_blocknr, &hash);
	if (error) {
		mb_cache_entry_free(ce);
		if (error == -EBUSY) {
			ea_bdebug(bh, "already in cache");
			error = 0;
		}
	} else {
		ea_bdebug(bh, "inserting [%x]", (int)hash);
		mb_cache_entry_release(ce);
	}
}