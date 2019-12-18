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
 int printf (char*,char const* const) ; 
 int /*<<< orphan*/  putchar (char) ; 
 size_t strlen (char const* const) ; 
 char* strstr (char*,char const* const) ; 

__attribute__((used)) static int case_print_hi(char* str, const char* const hi)
{
	if (!hi)
		return printf("%s", str);
	const size_t hilen = strlen(hi);
	char* savestr = strstr(str, hi);
	int nchr = 0;
	while (savestr)
	{
		for (;str < savestr; ++str, ++nchr)
			putchar(str[0]);
		nchr += printf("\033[7m%s\033[0m", hi); // decorate with underline.
		str += hilen;
		savestr = strstr(str, hi);
	}
	nchr += printf("%s", str);
	return nchr;
}