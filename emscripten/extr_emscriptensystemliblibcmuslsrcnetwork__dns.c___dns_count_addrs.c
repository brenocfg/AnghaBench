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
#define  RR_A 129 
#define  RR_AAAA 128 
 int __dns_get_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int,unsigned char const*,int const,int /*<<< orphan*/ ) ; 

int __dns_count_addrs(const unsigned char *r, int cnt)
{
	int found=0, res, i;
	static const int p[2][2] = { { 4, RR_A }, { 16, RR_AAAA } };

	while (cnt--) {
		for (i=0; i<2; i++) {
			res = __dns_get_rr(0, 0, p[i][0], -1, r, p[i][1], 0);
			if (res < 0) return res;
			found += res;
		}
		r += 512;
	}
	return found;
}