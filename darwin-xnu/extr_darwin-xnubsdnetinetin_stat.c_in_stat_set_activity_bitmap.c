#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u_int64_t ;
struct TYPE_3__ {scalar_t__ start; int* bitmap; } ;
typedef  TYPE_1__ activity_bitmap_t ;

/* Variables and functions */
 int IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE ; 
 int IN_STAT_ACTIVITY_BITMAP_TOTAL_SIZE ; 
 int IN_STAT_ACTIVITY_TIME_SEC_SHIFT ; 
 int IN_STAT_ACTIVITY_TOTAL_TIME ; 
 int IN_STAT_SET_MOST_SIGNIFICANT_BIT ; 

void
in_stat_set_activity_bitmap(activity_bitmap_t *activity, uint64_t now)
{
	uint64_t elapsed_time, slot;
	uint64_t *bitmap;
	if (activity->start == 0)
		activity->start = now;
	elapsed_time = now - activity->start;

	slot = elapsed_time >> IN_STAT_ACTIVITY_TIME_SEC_SHIFT;
	if (slot < IN_STAT_ACTIVITY_BITMAP_TOTAL_SIZE) {
		if (slot < IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE) {
			bitmap = &activity->bitmap[0];
		} else {
			bitmap = &activity->bitmap[1];
			slot -= IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE;
		}
		*bitmap |= (((u_int64_t) 1) << slot);
	} else {
		if (slot >= (IN_STAT_ACTIVITY_BITMAP_TOTAL_SIZE * 2)) {
			activity->start = now - IN_STAT_ACTIVITY_TOTAL_TIME;
			activity->bitmap[0] = activity->bitmap[1] = 0;
		} else {
			uint64_t shift =
			    slot - (IN_STAT_ACTIVITY_BITMAP_TOTAL_SIZE - 1);
			/*
			 * Move the start time and bitmap forward to
			 * cover the lost time
			 */
			activity->start +=
			    (shift << IN_STAT_ACTIVITY_TIME_SEC_SHIFT);
			if (shift > IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE) {
				activity->bitmap[0] = activity->bitmap[1];
				activity->bitmap[1] = 0;
				shift -= IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE;
				if (shift == IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE)
					activity->bitmap[0] = 0;
				else
					activity->bitmap[0] >>= shift;
			} else {
				uint64_t mask_lower, tmp;
				uint64_t b1_low, b0_high;

				/*
				 * generate a mask with all of lower
				 * 'shift' bits set
				 */
				tmp = (((uint64_t)1) << (shift - 1));
				mask_lower = ((tmp - 1) ^ tmp);
				activity->bitmap[0] >>= shift;
				b1_low = (activity->bitmap[1] & mask_lower);

				b0_high = (b1_low <<
				    (IN_STAT_ACTIVITY_BITMAP_FIELD_SIZE -
				     shift));
				activity->bitmap[0] |= b0_high;
				activity->bitmap[1] >>= shift;
			}
		}
		activity->bitmap[1] |= IN_STAT_SET_MOST_SIGNIFICANT_BIT;
	}
}