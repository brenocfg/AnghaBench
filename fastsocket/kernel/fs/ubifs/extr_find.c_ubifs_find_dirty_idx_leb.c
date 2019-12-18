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
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int find_dirtiest_idx_leb (struct ubifs_info*) ; 
 int find_dirty_idx_leb (struct ubifs_info*) ; 
 int get_idx_gc_leb (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_get_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_release_lprops (struct ubifs_info*) ; 

int ubifs_find_dirty_idx_leb(struct ubifs_info *c)
{
	int err;

	ubifs_get_lprops(c);

	/*
	 * We made an array of the dirtiest index LEB numbers as at the start of
	 * last commit.  Try that array first.
	 */
	err = find_dirtiest_idx_leb(c);

	/* Next try scanning the entire LPT */
	if (err == -ENOSPC)
		err = find_dirty_idx_leb(c);

	/* Finally take any index LEBs awaiting trivial GC */
	if (err == -ENOSPC)
		err = get_idx_gc_leb(c);

	ubifs_release_lprops(c);
	return err;
}