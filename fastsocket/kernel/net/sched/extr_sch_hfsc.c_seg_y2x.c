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
typedef  int u64 ;

/* Variables and functions */
 int HT_INFINITY ; 
 int ISM_MASK ; 
 int ISM_SHIFT ; 

__attribute__((used)) static inline u64
seg_y2x(u64 y, u64 ism)
{
	u64 x;

	if (y == 0)
		x = 0;
	else if (ism == HT_INFINITY)
		x = HT_INFINITY;
	else {
		x = (y >> ISM_SHIFT) * ism
		    + (((y & ISM_MASK) * ism) >> ISM_SHIFT);
	}
	return x;
}