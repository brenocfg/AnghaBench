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
 int /*<<< orphan*/  HASZERO (size_t const) ; 
 size_t strlen (char const*) ; 

size_t strlcpy(char *d, const char *s, size_t n)
{
	char *d0 = d;
	size_t *wd;
	const size_t *ws;

	if (!n--) goto finish;
	if (((uintptr_t)s & ALIGN) == ((uintptr_t)d & ALIGN)) {
		for (; ((uintptr_t)s & ALIGN) && n && (*d=*s); n--, s++, d++);
		if (n && *s) {
			wd=(void *)d; ws=(const void *)s;
			for (; n>=sizeof(size_t) && !HASZERO(*ws);
			       n-=sizeof(size_t), ws++, wd++) *wd = *ws;
			d=(void *)wd; s=(const void *)ws;
		}
	}
	for (; n && (*d=*s); n--, s++, d++);
	*d = 0;
finish:
	return d-d0 + strlen(s);
}