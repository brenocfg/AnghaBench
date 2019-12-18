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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static void hdmi_infoframe_checksum(void *buffer, size_t size)
{
	u8 *ptr = buffer;
	u8 csum = 0;
	size_t i;

	/* compute checksum */
	for (i = 0; i < size; i++)
		csum += ptr[i];

	ptr[3] = 256 - csum;
}