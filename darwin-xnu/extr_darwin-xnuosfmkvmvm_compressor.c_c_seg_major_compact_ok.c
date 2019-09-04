#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* c_segment_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  asked_permission; } ;
struct TYPE_5__ {scalar_t__ c_bytes_used; scalar_t__ c_nextoffset; scalar_t__ c_nextslot; } ;

/* Variables and functions */
 scalar_t__ C_MAJOR_COMPACTION_SIZE_APPROPRIATE ; 
 scalar_t__ C_SEG_OFF_LIMIT ; 
 scalar_t__ C_SLOT_MAX_INDEX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ c_seg_major_compact_stats ; 

boolean_t
c_seg_major_compact_ok(
	c_segment_t c_seg_dst,
	c_segment_t c_seg_src)
{

	c_seg_major_compact_stats.asked_permission++;

	if (c_seg_src->c_bytes_used >= C_MAJOR_COMPACTION_SIZE_APPROPRIATE &&
	    c_seg_dst->c_bytes_used >= C_MAJOR_COMPACTION_SIZE_APPROPRIATE)
		return (FALSE);

	if (c_seg_dst->c_nextoffset >= C_SEG_OFF_LIMIT || c_seg_dst->c_nextslot >= C_SLOT_MAX_INDEX) {
		/*
		 * destination segment is full... can't compact
		 */
		return (FALSE);
	}

	return (TRUE);
}