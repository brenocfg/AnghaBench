#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const uint32_t ;
struct TYPE_5__ {int rnum; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_1__*,scalar_t__ const*) ; 

__attribute__((used)) static inline void ccv_array_add_unique_uint(ccv_array_t* ints, const uint32_t idx)
{
	int i;
	for (i = 0; i < ints->rnum; i++)
		if (*(uint32_t*)ccv_array_get(ints, i) == idx)
			return;
	ccv_array_push(ints, &idx);
}