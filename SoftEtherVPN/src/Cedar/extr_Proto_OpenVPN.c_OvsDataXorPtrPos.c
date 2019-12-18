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
typedef  scalar_t__ UCHAR ;

/* Variables and functions */

void OvsDataXorPtrPos(void *data, const UINT size)
{
	UINT i;
	UCHAR *buf;
	// Validate arguments
	if (data == NULL || size == 0)
	{
		return;
	}

	for (i = 0, buf = data; i < size; i++, buf++)
	{
		*buf = *buf ^ i + 1;
	}
}