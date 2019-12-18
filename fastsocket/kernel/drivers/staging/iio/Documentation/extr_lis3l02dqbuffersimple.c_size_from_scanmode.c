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

int size_from_scanmode(int numVals, int timestamp)
{
	if (numVals && timestamp)
		return 16;
	else if (timestamp)
		return 8;
	else
		return numVals*2;
}