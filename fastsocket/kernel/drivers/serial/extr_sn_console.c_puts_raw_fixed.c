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
 char* memchr (char const*,char,int) ; 

__attribute__((used)) static void puts_raw_fixed(int (*puts_raw) (const char *s, int len),
			   const char *s, int count)
{
	const char *s1;

	/* Output '\r' before each '\n' */
	while ((s1 = memchr(s, '\n', count)) != NULL) {
		puts_raw(s, s1 - s);
		puts_raw("\r\n", 2);
		count -= s1 + 1 - s;
		s = s1 + 1;
	}
	puts_raw(s, count);
}