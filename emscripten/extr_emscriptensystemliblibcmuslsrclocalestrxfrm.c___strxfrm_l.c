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
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

size_t __strxfrm_l(char *restrict dest, const char *restrict src, size_t n, locale_t loc)
{
	size_t l = strlen(src);
	if (n > l) strcpy(dest, src);
	return l;
}