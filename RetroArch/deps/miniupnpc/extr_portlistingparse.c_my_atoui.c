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
typedef  int UNSIGNED_INTEGER ;

/* Variables and functions */

__attribute__((used)) static UNSIGNED_INTEGER
my_atoui(const char * p, int l)
{
	UNSIGNED_INTEGER r = 0;
	while(l > 0 && *p)
	{
		if(*p >= '0' && *p <= '9')
			r = r*10 + (*p - '0');
		else
			break;
		p++;
		l--;
	}
	return r;
}