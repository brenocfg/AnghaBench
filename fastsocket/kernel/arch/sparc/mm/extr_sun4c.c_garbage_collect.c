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

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_ADDR (int) ; 
 scalar_t__ BUCKET_EMPTY ; 
 int /*<<< orphan*/  free_locked_segment (int /*<<< orphan*/ ) ; 
 scalar_t__* sun4c_bucket ; 

__attribute__((used)) static inline void garbage_collect(int entry)
{
	int start, end;

	/* 32 buckets per segment... */
	entry &= ~31;
	start = entry;
	for (end = (start + 32); start < end; start++)
		if (sun4c_bucket[start] != BUCKET_EMPTY)
			return;

	/* Entire segment empty, release it. */
	free_locked_segment(BUCKET_ADDR(entry));
}