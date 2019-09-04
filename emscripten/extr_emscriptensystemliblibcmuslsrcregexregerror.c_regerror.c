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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 char* LCTRANS_CUR (char const*) ; 
 char* messages ; 
 size_t snprintf (char*,size_t,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

size_t regerror(int e, const regex_t *restrict preg, char *restrict buf, size_t size)
{
	const char *s;
	for (s=messages; e && *s; e--, s+=strlen(s)+1);
	if (!*s) s++;
	s = LCTRANS_CUR(s);
	return 1+snprintf(buf, size, "%s", s);
}