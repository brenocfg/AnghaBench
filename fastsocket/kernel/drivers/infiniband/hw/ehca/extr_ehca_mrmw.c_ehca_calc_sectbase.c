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
 int EHCA_DIR_INDEX_SHIFT ; 
 int EHCA_TOP_INDEX_SHIFT ; 
 unsigned long SECTION_SIZE_BITS ; 
 void* abs_to_virt (unsigned long) ; 

__attribute__((used)) static inline void *ehca_calc_sectbase(int top, int dir, int idx)
{
	unsigned long ret = idx;
	ret |= dir << EHCA_DIR_INDEX_SHIFT;
	ret |= top << EHCA_TOP_INDEX_SHIFT;
	return abs_to_virt(ret << SECTION_SIZE_BITS);
}