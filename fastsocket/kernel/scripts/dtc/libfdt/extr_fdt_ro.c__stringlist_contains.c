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
 char* memchr (char const*,char,int) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int _stringlist_contains(const char *strlist, int listlen, const char *str)
{
	int len = strlen(str);
	const char *p;

	while (listlen >= len) {
		if (memcmp(str, strlist, len+1) == 0)
			return 1;
		p = memchr(strlist, '\0', listlen);
		if (!p)
			return 0; /* malformed strlist.. */
		listlen -= (p-strlist) + 1;
		strlist = p + 1;
	}
	return 0;
}