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
 int /*<<< orphan*/ ** h_fp ; 

int Devices_H_CountOpen(void)
{
	int r = 0;
	int i;
	for (i = 0; i < 8; i++)
		if (h_fp[i] != NULL)
			r++;
	return r;
}