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
typedef  int u32 ;

/* Variables and functions */
 int FL_DELTA_MASK ; 
 int FL_DELTA_SHIFT ; 
 int XV_MAX_ALLOC_SIZE ; 
 int XV_MIN_ALLOC_SIZE ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 get_index_for_insert(u32 size)
{
	if (unlikely(size > XV_MAX_ALLOC_SIZE))
		size = XV_MAX_ALLOC_SIZE;
	size &= ~FL_DELTA_MASK;
	return (size - XV_MIN_ALLOC_SIZE) >> FL_DELTA_SHIFT;
}