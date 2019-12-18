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
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */

void OvsDataReverse(void *data, const UINT size)
{
	UINT i;
	UCHAR tmp;
	UCHAR *buf_start, *buf_end;
	// Validate arguments
	if (data == NULL || size < 3)
	{
		return;
	}

	for (i = 0, buf_start = (UCHAR *)data + 1, buf_end = (UCHAR *)data + (size - 1); i < (size - 1 ) / 2; i++, buf_start++, buf_end--)
	{
		tmp = *buf_start;
		*buf_start = *buf_end;
		*buf_end = tmp;
	}
}