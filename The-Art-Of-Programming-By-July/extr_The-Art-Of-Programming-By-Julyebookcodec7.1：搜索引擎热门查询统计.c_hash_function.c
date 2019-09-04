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
 int HASHLEN ; 

int hash_function(char const *p)
{
	int value = 0;
	while (*p != '\0')
	{
		value = value * 31 + *p++;
		if (value > HASHLEN)
			value = value % HASHLEN;
	}
	return value;
}