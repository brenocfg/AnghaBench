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
 unsigned long FB_SHIFT_LOW (struct fb_info*,unsigned long,int) ; 
 unsigned long comp (unsigned long const,unsigned long,unsigned long) ; 
 int ffs (int) ; 

__attribute__((used)) static void
bitcpy_rev(struct fb_info *p, unsigned long *dst, int dst_idx,
		const unsigned long *src, int src_idx, int bits, unsigned n)
{
	unsigned long first, last;
	int shift;

	dst += (n-1)/bits;
	src += (n-1)/bits;
	if ((n-1) % bits) {
		dst_idx += (n-1) % bits;
		dst += dst_idx >> (ffs(bits) - 1);
		dst_idx &= bits - 1;
		src_idx += (n-1) % bits;
		src += src_idx >> (ffs(bits) - 1);
		src_idx &= bits - 1;
	}

	shift = dst_idx-src_idx;

	first = FB_SHIFT_LOW(p, ~0UL, bits - 1 - dst_idx);
	last = ~(FB_SHIFT_LOW(p, ~0UL, bits - 1 - ((dst_idx-n) % bits)));

	if (!shift) {
		/* Same alignment for source and dest */
		if ((unsigned long)dst_idx+1 >= n) {
			/* Single word */
			if (last)
				first &= last;
			*dst = comp(*src, *dst, first);
		} else {
			/* Multiple destination words */

			/* Leading bits */
			if (first != ~0UL) {
				*dst = comp(*src, *dst, first);
				dst--;
				src--;
				n -= dst_idx+1;
			}

			/* Main chunk */
			n /= bits;
			while (n >= 8) {
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				*dst-- = *src--;
				n -= 8;
			}
			while (n--)
				*dst-- = *src--;
			/* Trailing bits */
			if (last)
				*dst = comp(*src, *dst, last);
		}
	} else {
		/* Different alignment for source and dest */

		int const left = -shift & (bits-1);
		int const right = shift & (bits-1);

		if ((unsigned long)dst_idx+1 >= n) {
			/* Single destination word */
			if (last)
				first &= last;
			if (shift < 0) {
				/* Single source word */
				*dst = comp(*src << left, *dst, first);
			} else if (1+(unsigned long)src_idx >= n) {
				/* Single source word */
				*dst = comp(*src >> right, *dst, first);
			} else {
				/* 2 source words */
				*dst = comp(*src >> right | *(src-1) << left,
					    *dst, first);
			}
		} else {
			/* Multiple destination words */
			/** We must always remember the last value read,
			    because in case SRC and DST overlap bitwise (e.g.
			    when moving just one pixel in 1bpp), we always
			    collect one full long for DST and that might
			    overlap with the current long from SRC. We store
			    this value in 'd0'. */
			unsigned long d0, d1;
			int m;

			d0 = *src--;
			/* Leading bits */
			if (shift < 0) {
				/* Single source word */
				*dst = comp(d0 << left, *dst, first);
			} else {
				/* 2 source words */
				d1 = *src--;
				*dst = comp(d0 >> right | d1 << left, *dst,
					    first);
				d0 = d1;
			}
			dst--;
			n -= dst_idx+1;

			/* Main chunk */
			m = n % bits;
			n /= bits;
			while (n >= 4) {
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
				n -= 4;
			}
			while (n--) {
				d1 = *src--;
				*dst-- = d0 >> right | d1 << left;
				d0 = d1;
			}

			/* Trailing bits */
			if (last) {
				if (m <= left) {
					/* Single source word */
					*dst = comp(d0 >> right, *dst, last);
				} else {
					/* 2 source words */
					d1 = *src;
					*dst = comp(d0 >> right | d1 << left,
						    *dst, last);
				}
			}
		}
	}
}