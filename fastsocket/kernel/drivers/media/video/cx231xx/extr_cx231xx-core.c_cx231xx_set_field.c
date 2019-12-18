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

u32 cx231xx_set_field(u32 field_mask, u32 data)
{
	u32 temp;

	for (temp = field_mask; (temp & 1) == 0; temp >>= 1)
		data <<= 1;

	return data;
}