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
typedef  scalar_t__ s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */

s16 qm_add16(s16 op1, s16 op2)
{
	s16 result;
	s32 temp = (s32) op1 + (s32) op2;
	if (temp > (s32) 0x7fff)
		result = (s16) 0x7fff;
	else if (temp < (s32) 0xffff8000)
		result = (s16) 0xffff8000;
	else
		result = (s16) temp;

	return result;
}