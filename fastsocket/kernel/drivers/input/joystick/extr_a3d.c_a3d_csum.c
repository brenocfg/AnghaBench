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

__attribute__((used)) static int a3d_csum(char *data, int count)
{
	int i, csum = 0;

	for (i = 0; i < count - 2; i++)
		csum += data[i];
	return (csum & 0x3f) != ((data[count - 2] << 3) | data[count - 1]);
}