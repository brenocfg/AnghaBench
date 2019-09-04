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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int memcmp (void*,void*,size_t) ; 

int Cmp(void *p1, void *p2, UINT size)
{
	// Validate arguments
	if (p1 == NULL || p2 == NULL || size == 0)
	{
		return 0;
	}

	return memcmp(p1, p2, (size_t)size);
}