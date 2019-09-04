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
 char* malloc (size_t) ; 
 char* memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char *__strdup(const char *s)
{
	size_t l = strlen(s);
	char *d = malloc(l+1);
	if (!d) return NULL;
	return memcpy(d, s, l+1);
}