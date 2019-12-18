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
 scalar_t__ Util_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

char *Util_strdup(const char *s)
{
	/* don't use strdup(): it is unavailable on WinCE */
	size_t size = strlen(s) + 1;
	char *ptr = (char *) Util_malloc(size);
	memcpy(ptr, s, size); /* faster than strcpy(ptr, s) */
	return ptr;
}