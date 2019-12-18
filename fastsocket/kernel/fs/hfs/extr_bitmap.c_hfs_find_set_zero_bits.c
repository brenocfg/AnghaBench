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
typedef  int u32 ;
typedef  int __be32 ;

/* Variables and functions */
 int be32_to_cpu (int) ; 
 void* cpu_to_be32 (int) ; 
 int min (int,int) ; 

__attribute__((used)) static u32 hfs_find_set_zero_bits(__be32 *bitmap, u32 size, u32 offset, u32 *max)
{
	__be32 *curr, *end;
	u32 mask, start, len, n;
	__be32 val;
	int i;

	len = *max;
	if (!len)
		return size;

	curr = bitmap + (offset / 32);
	end = bitmap + ((size + 31) / 32);

	/* scan the first partial u32 for zero bits */
	val = *curr;
	if (~val) {
		n = be32_to_cpu(val);
		i = offset % 32;
		mask = (1U << 31) >> i;
		for (; i < 32; mask >>= 1, i++) {
			if (!(n & mask))
				goto found;
		}
	}

	/* scan complete u32s for the first zero bit */
	while (++curr < end) {
		val = *curr;
		if (~val) {
			n = be32_to_cpu(val);
			mask = 1 << 31;
			for (i = 0; i < 32; mask >>= 1, i++) {
				if (!(n & mask))
					goto found;
			}
		}
	}
	return size;

found:
	start = (curr - bitmap) * 32 + i;
	if (start >= size)
		return start;
	/* do any partial u32 at the start */
	len = min(size - start, len);
	while (1) {
		n |= mask;
		if (++i >= 32)
			break;
		mask >>= 1;
		if (!--len || n & mask)
			goto done;
	}
	if (!--len)
		goto done;
	*curr++ = cpu_to_be32(n);
	/* do full u32s */
	while (1) {
		n = be32_to_cpu(*curr);
		if (len < 32)
			break;
		if (n) {
			len = 32;
			break;
		}
		*curr++ = cpu_to_be32(0xffffffff);
		len -= 32;
	}
	/* do any partial u32 at end */
	mask = 1U << 31;
	for (i = 0; i < len; i++) {
		if (n & mask)
			break;
		n |= mask;
		mask >>= 1;
	}
done:
	*curr = cpu_to_be32(n);
	*max = (curr - bitmap) * 32 + i - start;
	return start;
}