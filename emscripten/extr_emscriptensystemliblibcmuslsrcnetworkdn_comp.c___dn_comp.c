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
 int getlens (unsigned char*,char const*,size_t) ; 
 int match (int*,unsigned char*,unsigned char*,char const*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 size_t strnlen (char const*,int) ; 

int __dn_comp(const char *src, unsigned char *dst, int space, unsigned char **dnptrs, unsigned char **lastdnptr)
{
	int i, j, n, m=0, offset, bestlen=0, bestoff;
	unsigned char lens[127];
	unsigned char **p;
	const char *end;
	size_t l = strnlen(src, 255);
	if (l && src[l-1] == '.') l--;
	if (l>253 || space<=0) return -1;
	if (!l) {
		*dst = 0;
		return 1;
	}
	end = src+l;
	n = getlens(lens, src, l);
	if (!n) return -1;

	p = dnptrs;
	if (p && *p) for (p++; *p; p++) {
		m = match(&offset, *dnptrs, *p, end, lens, n);
		if (m > bestlen) {
			bestlen = m;
			bestoff = offset;
			if (m == l)
				break;
		}
	}

	/* encode unmatched part */
	if (space < l-bestlen+2+(bestlen-1 < l-1)) return -1;
	memcpy(dst+1, src, l-bestlen);
	for (i=j=0; i<l-bestlen; i+=lens[j++]+1)
		dst[i] = lens[j];

	/* add tail */
	if (bestlen) {
		dst[i++] = 0xc0 | bestoff>>8;
		dst[i++] = bestoff;
	} else
		dst[i++] = 0;

	/* save dst pointer */
	if (i>2 && lastdnptr && dnptrs && *dnptrs) {
		while (*p) p++;
		if (p+1 < lastdnptr) {
			*p++ = dst;
			*p=0;
		}
	}
	return i;
}