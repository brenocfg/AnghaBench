#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hpt_info {size_t clock; TYPE_1__* timings; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** clock_table; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* xfer_speeds ; 

__attribute__((used)) static u32 get_speed_setting(u8 speed, struct hpt_info *info)
{
	int i;

	/*
	 * Lookup the transfer mode table to get the index into
	 * the timing table.
	 *
	 * NOTE: For XFER_PIO_SLOW, PIO mode 0 timings will be used.
	 */
	for (i = 0; i < ARRAY_SIZE(xfer_speeds) - 1; i++)
		if (xfer_speeds[i] == speed)
			break;

	return info->timings->clock_table[info->clock][i];
}