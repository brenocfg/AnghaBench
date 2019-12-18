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
typedef  scalar_t__ u64 ;
struct ipz_queue {scalar_t__ qe_size; scalar_t__ queue_length; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 ipz_queue_advance_offset(struct ipz_queue *queue, u64 offset)
{
	offset += queue->qe_size;
	if (offset >= queue->queue_length) offset = 0;
	return offset;
}