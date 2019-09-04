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
 scalar_t__ __dn_expand (unsigned char const*,unsigned char const*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char const*,int) ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 

int __dns_get_rr(void *dest, size_t stride, size_t maxlen, size_t limit, const unsigned char *r, int rr, int dec)
{
	int qdcount, ancount;
	const unsigned char *p;
	char tmp[256];
	int found = 0;
	int len;

	if ((r[3]&15)) return 0;
	p = r+12;
	qdcount = r[4]*256 + r[5];
	ancount = r[6]*256 + r[7];
	if (qdcount+ancount > 64) return -1;
	while (qdcount--) {
		while (p-r < 512 && *p-1U < 127) p++;
		if (*p>193 || (*p==193 && p[1]>254) || p>r+506)
			return -1;
		p += 5 + !!*p;
	}
	while (ancount--) {
		while (p-r < 512 && *p-1U < 127) p++;
		if (*p>193 || (*p==193 && p[1]>254) || p>r+506)
			return -1;
		p += 1 + !!*p;
		len = p[8]*256 + p[9];
		if (p+len > r+512) return -1;
		if (p[1]==rr && len <= maxlen) {
			if (dec && __dn_expand(r, r+512, p+10, tmp, sizeof tmp)<0)
				return -1;
			if (dest && limit) {
				if (dec) strcpy(dest, tmp);
				else memcpy(dest, p+10, len);
				dest = (char *)dest + stride;
				limit--;
			}
			found++;
		}
		p += 10 + len;
	}
	return found;
}