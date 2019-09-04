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
typedef  int wctype_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

wctype_t wctype(const char *s)
{
	int i;
	const char *p;
	/* order must match! */
	static const char names[] =
		"alnum\0" "alpha\0" "blank\0"
		"cntrl\0" "digit\0" "graph\0"
		"lower\0" "print\0" "punct\0"
		"space\0" "upper\0" "xdigit";
	for (i=1, p=names; *p; i++, p+=6)
		if (*s == *p && !strcmp(s, p))
			return i;
	return 0;
}