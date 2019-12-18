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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__* _ccv_base_table ; 
 int* _ccv_shift_table ; 

void ccv_float_to_half_precision(float* f, uint16_t* h, size_t len)
{
	int i;
	uint32_t* u = (uint32_t*)f;
	for (i = 0; i < len; i++)
		h[i] = _ccv_base_table[(u[i] >> 23) & 0x1ff] + ((u[i] & 0x007fffff) >> _ccv_shift_table[(u[i] >> 23) & 0x1ff]);
}