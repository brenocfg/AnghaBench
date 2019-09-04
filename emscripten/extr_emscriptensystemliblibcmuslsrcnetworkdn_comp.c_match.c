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
 int getoffs (short*,unsigned char const*,unsigned char const*) ; 
 scalar_t__ memcmp (unsigned char const*,char const*,int) ; 

__attribute__((used)) static int match(int *offset, const unsigned char *base, const unsigned char *dn,
	const char *end, const unsigned char *lens, int nlen)
{
	int l, o, m=0;
	short offs[128];
	int noff = getoffs(offs, base, dn);
	if (!noff) return 0;
	for (;;) {
		l = lens[--nlen];
		o = offs[--noff];
		end -= l;
		if (l != base[o] || memcmp(base+o+1, end, l))
			return m;
		*offset = o;
		m += l;
		if (nlen) m++;
		if (!nlen || !noff) return m;
		end--;
	}
}