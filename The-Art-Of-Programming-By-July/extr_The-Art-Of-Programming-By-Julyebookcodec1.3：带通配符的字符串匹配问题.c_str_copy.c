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

void str_copy(char *a, const char *b, int len)
{
	//拷贝字符串 a = b
	for (; len > 0; --len, ++b, ++a)
	{
		*a = *b;
	}
	*a = 0;
}