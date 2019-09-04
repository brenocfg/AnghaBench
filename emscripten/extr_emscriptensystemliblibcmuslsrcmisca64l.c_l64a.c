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
typedef  int uint32_t ;

/* Variables and functions */
 char* digits ; 

char *l64a(long x0)
{
	static char s[7];
	char *p;
	uint32_t x = x0;
	for (p=s; x; p++, x>>=6)
		*p = digits[x&63];
	*p = 0;
	return s;
}