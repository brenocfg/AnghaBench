#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ confidence; } ;
struct TYPE_7__ {TYPE_1__ classification; } ;
typedef  TYPE_2__ ccv_comp_t ;
struct TYPE_8__ {int rnum; } ;
typedef  TYPE_3__ ccv_array_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 

__attribute__((used)) static void _ccv_tld_box_percolate_down(ccv_array_t* good, int i)
{
	for (;;)
	{
		int left = 2 * (i + 1) - 1;
		int right = 2 * (i + 1);
		int smallest = i;
		ccv_comp_t* smallest_comp = (ccv_comp_t*)ccv_array_get(good, smallest);
		if (left < good->rnum)
		{
			ccv_comp_t* left_comp = (ccv_comp_t*)ccv_array_get(good, left);
			if (left_comp->classification.confidence < smallest_comp->classification.confidence)
				smallest = left;
		}
		if (right < good->rnum)
		{
			ccv_comp_t* right_comp = (ccv_comp_t*)ccv_array_get(good, right);
			if (right_comp->classification.confidence < smallest_comp->classification.confidence)
				smallest = right;
		}
		if (smallest == i)
			break;
		ccv_comp_t c = *(ccv_comp_t*)ccv_array_get(good, smallest);
		*(ccv_comp_t*)ccv_array_get(good, smallest) = *(ccv_comp_t*)ccv_array_get(good, i);
		*(ccv_comp_t*)ccv_array_get(good, i) = c;
		i = smallest;
	}
}