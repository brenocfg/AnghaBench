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
typedef  scalar_t__ u32 ;
struct il_traffic_load {scalar_t__ time_stamp; size_t head; scalar_t__ queue_count; scalar_t__* packet_count; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 scalar_t__ TID_MAX_TIME_DIFF ; 
 scalar_t__ TID_QUEUE_CELL_SPACING ; 
 size_t TID_QUEUE_MAX_SIZE ; 

__attribute__((used)) static void
il4965_rs_tl_rm_old_stats(struct il_traffic_load *tl, u32 curr_time)
{
	/* The oldest age we want to keep */
	u32 oldest_time = curr_time - TID_MAX_TIME_DIFF;

	while (tl->queue_count && tl->time_stamp < oldest_time) {
		tl->total -= tl->packet_count[tl->head];
		tl->packet_count[tl->head] = 0;
		tl->time_stamp += TID_QUEUE_CELL_SPACING;
		tl->queue_count--;
		tl->head++;
		if (tl->head >= TID_QUEUE_MAX_SIZE)
			tl->head = 0;
	}
}