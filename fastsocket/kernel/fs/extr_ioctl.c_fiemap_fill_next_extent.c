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
typedef  void* u64 ;
typedef  int u32 ;
struct fiemap_extent_info {scalar_t__ fi_extents_max; scalar_t__ fi_extents_mapped; struct fiemap_extent* fi_extents_start; } ;
struct fiemap_extent {int fe_flags; void* fe_length; void* fe_physical; void* fe_logical; } ;
typedef  int /*<<< orphan*/  extent ;

/* Variables and functions */
 int EFAULT ; 
 int FIEMAP_EXTENT_ENCODED ; 
 int FIEMAP_EXTENT_LAST ; 
 int FIEMAP_EXTENT_NOT_ALIGNED ; 
 int FIEMAP_EXTENT_UNKNOWN ; 
 int SET_NOT_ALIGNED_FLAGS ; 
 int SET_NO_UNMOUNTED_IO_FLAGS ; 
 int SET_UNKNOWN_FLAGS ; 
 scalar_t__ copy_to_user (struct fiemap_extent*,struct fiemap_extent*,int) ; 
 int /*<<< orphan*/  memset (struct fiemap_extent*,int /*<<< orphan*/ ,int) ; 

int fiemap_fill_next_extent(struct fiemap_extent_info *fieinfo, u64 logical,
			    u64 phys, u64 len, u32 flags)
{
	struct fiemap_extent extent;
	struct fiemap_extent *dest = fieinfo->fi_extents_start;

	/* only count the extents */
	if (fieinfo->fi_extents_max == 0) {
		fieinfo->fi_extents_mapped++;
		return (flags & FIEMAP_EXTENT_LAST) ? 1 : 0;
	}

	if (fieinfo->fi_extents_mapped >= fieinfo->fi_extents_max)
		return 1;

	if (flags & SET_UNKNOWN_FLAGS)
		flags |= FIEMAP_EXTENT_UNKNOWN;
	if (flags & SET_NO_UNMOUNTED_IO_FLAGS)
		flags |= FIEMAP_EXTENT_ENCODED;
	if (flags & SET_NOT_ALIGNED_FLAGS)
		flags |= FIEMAP_EXTENT_NOT_ALIGNED;

	memset(&extent, 0, sizeof(extent));
	extent.fe_logical = logical;
	extent.fe_physical = phys;
	extent.fe_length = len;
	extent.fe_flags = flags;

	dest += fieinfo->fi_extents_mapped;
	if (copy_to_user(dest, &extent, sizeof(extent)))
		return -EFAULT;

	fieinfo->fi_extents_mapped++;
	if (fieinfo->fi_extents_mapped == fieinfo->fi_extents_max)
		return 1;
	return (flags & FIEMAP_EXTENT_LAST) ? 1 : 0;
}