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
typedef  scalar_t__ scale3x_uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void scale3x_8_def_border(scale3x_uint8* __restrict__ dst, const scale3x_uint8* __restrict__ src0, const scale3x_uint8* __restrict__ src1, const scale3x_uint8* __restrict__ src2, unsigned count)
{
	assert(count >= 2);

	/* first pixel */
	dst[0] = src1[0];
	dst[1] = src1[0];
	if (src1[1] == src0[0] && src2[0] != src0[0])
		dst[2] = src0[0];
	else
		dst[2] = src1[0];
	++src0;
	++src1;
	++src2;
	dst += 3;

	/* central pixels */
	count -= 2;
	while (count) {
		if (src0[0] != src2[0] && src1[-1] != src1[1]) {
			dst[0] = src1[-1] == src0[0] ? src1[-1] : src1[0];
			dst[1] = (src1[-1] == src0[0] && src1[0] != src0[1]) || (src1[1] == src0[0] && src1[0] != src0[-1]) ? src0[0] : src1[0];
			dst[2] = src1[1] == src0[0] ? src1[1] : src1[0];
		} else {
			dst[0] = src1[0];
			dst[1] = src1[0];
			dst[2] = src1[0];
		}

		++src0;
		++src1;
		++src2;
		dst += 3;
		--count;
	}

	/* last pixel */
	if (src1[-1] == src0[0] && src2[0] != src0[0])
		dst[0] = src0[0];
	else
		dst[0] = src1[0];
	dst[1] = src1[0];
	dst[2] = src1[0];
}