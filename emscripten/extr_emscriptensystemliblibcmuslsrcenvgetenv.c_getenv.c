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
 char** __environ ; 
 scalar_t__ strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

char *getenv(const char *name)
{
	int i;
	size_t l = strlen(name);
	if (!__environ || !*name || strchr(name, '=')) return NULL;
	for (i=0; __environ[i] && (strncmp(name, __environ[i], l)
		|| __environ[i][l] != '='); i++);
	if (__environ[i]) return __environ[i] + l+1;
	return NULL;
}