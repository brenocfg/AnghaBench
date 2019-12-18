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
struct fb_info {int dummy; } ;

/* Variables and functions */
 unsigned long FB_SHIFT_HIGH (struct fb_info*,unsigned long,int) ; 
 unsigned long comp (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void
bitfill_aligned_rev(struct fb_info *p, unsigned long *dst, int dst_idx,
		    unsigned long pat, unsigned n, int bits)
{
	unsigned long val = pat;
	unsigned long first, last;

	if (!n)
		return;

	first = FB_SHIFT_HIGH(p, ~0UL, dst_idx);
	last = ~(FB_SHIFT_HIGH(p, ~0UL, (dst_idx+n) % bits));

	if (dst_idx+n <= bits) {
		/* Single word */
		if (last)
			first &= last;
		*dst = comp(*dst ^ val, *dst, first);
	} else {
		/* Multiple destination words */
		/* Leading bits */
		if (first!=0UL) {
			*dst = comp(*dst ^ val, *dst, first);
			dst++;
			n -= bits - dst_idx;
		}

		/* Main chunk */
		n /= bits;
		while (n >= 8) {
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			*dst++ ^= val;
			n -= 8;
		}
		while (n--)
			*dst++ ^= val;
		/* Trailing bits */
		if (last)
			*dst = comp(*dst ^ val, *dst, last);
	}
}