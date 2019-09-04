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
 int /*<<< orphan*/  NdisFreeMemory (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SlFree(void *p)
{
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	// Release the memory
	NdisFreeMemory(p, 0, 0);
}