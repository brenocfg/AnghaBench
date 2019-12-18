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

void mix_16h_to_32(int *dest_buf, short *mp3_buf, int count)
{
	while (count--)
	{
		*dest_buf++ += *mp3_buf++ >> 1;
	}
}