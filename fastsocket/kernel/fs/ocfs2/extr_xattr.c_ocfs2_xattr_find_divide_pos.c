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
struct ocfs2_xattr_header {int /*<<< orphan*/  xh_count; struct ocfs2_xattr_entry* xh_entries; } ;
struct ocfs2_xattr_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ cmp_xe (struct ocfs2_xattr_entry*,struct ocfs2_xattr_entry*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_find_divide_pos(struct ocfs2_xattr_header *xh)
{
	struct ocfs2_xattr_entry *entries = xh->xh_entries;
	int count = le16_to_cpu(xh->xh_count);
	int delta, middle = count / 2;

	/*
	 * We start at the middle.  Each step gets farther away in both
	 * directions.  We therefore hit the change in hash value
	 * nearest to the middle.  Note that this loop does not execute for
	 * count < 2.
	 */
	for (delta = 0; delta < middle; delta++) {
		/* Let's check delta earlier than middle */
		if (cmp_xe(&entries[middle - delta - 1],
			   &entries[middle - delta]))
			return middle - delta;

		/* For even counts, don't walk off the end */
		if ((middle + delta + 1) == count)
			continue;

		/* Now try delta past middle */
		if (cmp_xe(&entries[middle + delta],
			   &entries[middle + delta + 1]))
			return middle + delta + 1;
	}

	/* Every entry had the same hash */
	return count;
}