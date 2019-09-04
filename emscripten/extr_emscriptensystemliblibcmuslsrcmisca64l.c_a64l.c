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
typedef  long int32_t ;

/* Variables and functions */
 char const* digits ; 
 char* strchr (char const*,char const) ; 

long a64l(const char *s)
{
	int e;
	uint32_t x = 0;
	for (e=0; e<36 && *s; e+=6, s++) {
		const char *d = strchr(digits, *s);
		if (!d) break;
		x |= (uint32_t)(d-digits)<<e;
	}
	return (int32_t)x;
}