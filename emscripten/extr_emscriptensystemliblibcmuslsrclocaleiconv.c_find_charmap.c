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
 unsigned char const* charmaps ; 
 int /*<<< orphan*/  fuzzycmp (void const*,unsigned char const*) ; 
 scalar_t__ strlen (void*) ; 

__attribute__((used)) static size_t find_charmap(const void *name)
{
	const unsigned char *s;
	if (!*(char *)name) name=charmaps; /* "utf8" */
	for (s=charmaps; *s; ) {
		if (!fuzzycmp(name, s)) {
			for (; *s; s+=strlen((void *)s)+1);
			return s+1-charmaps;
		}
		s += strlen((void *)s)+1;
		if (!*s) {
			if (s[1] > 0200) s+=2;
			else s+=2+(128U-s[1])/4*5;
		}
	}
	return -1;
}