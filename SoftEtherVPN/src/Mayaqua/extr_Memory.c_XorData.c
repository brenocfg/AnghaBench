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
typedef  int UCHAR ;

/* Variables and functions */

void XorData(void *dst, void *src1, void *src2, UINT size)
{
	UINT i;
	UCHAR *d, *c1, *c2;
	// Validate arguments
	if (dst == NULL || src1 == NULL || src2 == NULL || size == 0)
	{
		return;
	}

	d = (UCHAR *)dst;
	c1 = (UCHAR *)src1;
	c2 = (UCHAR *)src2;

	for (i = 0;i < size;i++)
	{
		*d = (*c1) ^ (*c2);

		d++;
		c1++;
		c2++;
	}
}