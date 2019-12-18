#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s64 ;
struct TYPE_15__ {scalar_t__ vcn; scalar_t__ length; scalar_t__ lcn; } ;
typedef  TYPE_1__ runlist_element ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 scalar_t__ LCN_HOLE ; 
 scalar_t__ LCN_RL_NOT_MAPPED ; 
 int /*<<< orphan*/  __ntfs_rl_merge (TYPE_1__*,TYPE_1__*) ; 
 int ntfs_are_rl_mergeable (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_rl_mc (TYPE_1__*,int,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ntfs_rl_mm (TYPE_1__*,int,int,int) ; 
 TYPE_1__* ntfs_rl_realloc (TYPE_1__*,int,int) ; 

__attribute__((used)) static inline runlist_element *ntfs_rl_insert(runlist_element *dst,
		int dsize, runlist_element *src, int ssize, int loc)
{
	bool left = false;	/* Left end of @src needs merging. */
	bool disc = false;	/* Discontinuity between @dst and @src. */
	int marker;		/* End of the inserted runs. */

	BUG_ON(!dst);
	BUG_ON(!src);

	/*
	 * disc => Discontinuity between the end of @dst and the start of @src.
	 *	   This means we might need to insert a "not mapped" run.
	 */
	if (loc == 0)
		disc = (src[0].vcn > 0);
	else {
		s64 merged_length;

		left = ntfs_are_rl_mergeable(dst + loc - 1, src);

		merged_length = dst[loc - 1].length;
		if (left)
			merged_length += src->length;

		disc = (src[0].vcn > dst[loc - 1].vcn + merged_length);
	}
	/*
	 * Space required: @dst size + @src size, less one if we merged, plus
	 * one if there was a discontinuity.
	 */
	dst = ntfs_rl_realloc(dst, dsize, dsize + ssize - left + disc);
	if (IS_ERR(dst))
		return dst;
	/*
	 * We are guaranteed to succeed from here so can start modifying the
	 * original runlist.
	 */
	if (left)
		__ntfs_rl_merge(dst + loc - 1, src);
	/*
	 * First run after the @src runs that have been inserted.
	 * Nominally,  @marker equals @loc + @ssize, i.e. location + number of
	 * runs in @src.  However, if @left, then the first run in @src has
	 * been merged with one in @dst.  And if @disc, then @dst and @src do
	 * not meet and we need an extra run to fill the gap.
	 */
	marker = loc + ssize - left + disc;

	/* Move the tail of @dst out of the way, then copy in @src. */
	ntfs_rl_mm(dst, marker, loc, dsize - loc);
	ntfs_rl_mc(dst, loc + disc, src, left, ssize - left);

	/* Adjust the VCN of the first run after the insertion... */
	dst[marker].vcn = dst[marker - 1].vcn + dst[marker - 1].length;
	/* ... and the length. */
	if (dst[marker].lcn == LCN_HOLE || dst[marker].lcn == LCN_RL_NOT_MAPPED)
		dst[marker].length = dst[marker + 1].vcn - dst[marker].vcn;

	/* Writing beyond the end of the file and there is a discontinuity. */
	if (disc) {
		if (loc > 0) {
			dst[loc].vcn = dst[loc - 1].vcn + dst[loc - 1].length;
			dst[loc].length = dst[loc + 1].vcn - dst[loc].vcn;
		} else {
			dst[loc].vcn = 0;
			dst[loc].length = dst[loc + 1].vcn;
		}
		dst[loc].lcn = LCN_RL_NOT_MAPPED;
	}
	return dst;
}