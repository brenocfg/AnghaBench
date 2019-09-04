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
 uintptr_t ALIGN ; 
 int /*<<< orphan*/  HASZERO (size_t) ; 
 int ONES ; 
 int strlen (char const*) ; 

char *__strchrnul(const char *s, int c)
{
	size_t *w, k;

	c = (unsigned char)c;
	if (!c) return (char *)s + strlen(s);

	for (; (uintptr_t)s % ALIGN; s++)
		if (!*s || *(unsigned char *)s == c) return (char *)s;
	k = ONES * c;
	for (w = (void *)s; !HASZERO(*w) && !HASZERO(*w^k); w++);
	for (s = (void *)w; *s && *(unsigned char *)s != c; s++);
	return (char *)s;
}