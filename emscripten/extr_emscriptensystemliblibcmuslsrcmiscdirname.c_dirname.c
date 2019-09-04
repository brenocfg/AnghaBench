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
 int strlen (char*) ; 

char *dirname(char *s)
{
	size_t i;
	if (!s || !*s) return ".";
	i = strlen(s)-1;
	for (; s[i]=='/'; i--) if (!i) return "/";
	for (; s[i]!='/'; i--) if (!i) return ".";
	for (; s[i]=='/'; i--) if (!i) return "/";
	s[i+1] = 0;
	return s;
}