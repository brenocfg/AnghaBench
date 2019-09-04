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

char *__stpcpy(char *restrict d, const char *restrict s)
{
	size_t *wd;
	const size_t *ws;

	if ((uintptr_t)s % ALIGN == (uintptr_t)d % ALIGN) {
		for (; (uintptr_t)s % ALIGN; s++, d++)
			if (!(*d=*s)) return d;
		wd=(void *)d; ws=(const void *)s;
		for (; !HASZERO(*ws); *wd++ = *ws++);
		d=(void *)wd; s=(const void *)ws;
	}
	for (; (*d=*s); s++, d++);

	return d;
}