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

__attribute__((used)) static inline char *__strnend(const char *s, size_t n)
{
	register unsigned long r0 asm("0") = 0;
	const char *p = s + n;

	asm volatile ("0: srst  %0,%1\n"
		      "   jo    0b"
		      : "+d" (p), "+a" (s) : "d" (r0) : "cc" );
	return (char *) p;
}