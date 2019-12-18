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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 int mbtowc (scalar_t__*,char const*,int) ; 

__attribute__((used)) static wchar_t
get_wc(const char **p)
{
	wchar_t c;
	int chrlen;

	chrlen = mbtowc(&c, *p, 4);
	if (chrlen == 0)
		return 0;
	else if (chrlen == -1)
		c = 0;
	else
		*p += chrlen;
	return c;
}