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
 int PATH_MAX ; 
 int /*<<< orphan*/  define_config (char*,int) ; 
 scalar_t__ is_defined_config (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char tolower (int) ; 

__attribute__((used)) static void use_config(char *m, int slen)
{
	char s[PATH_MAX];
	char *p;

	if (is_defined_config(m, slen))
	    return;

	define_config(m, slen);

	memcpy(s, m, slen); s[slen] = 0;

	for (p = s; p < s + slen; p++) {
		if (*p == '_')
			*p = '/';
		else
			*p = tolower((int)*p);
	}
	printf("    $(wildcard include/config/%s.h) \\\n", s);
}