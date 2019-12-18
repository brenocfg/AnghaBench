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
 unsigned char* SCDST (int) ; 
 unsigned char* SCSRC (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  scale2x_mmx_emms () ; 
 int /*<<< orphan*/  stage_scale2x (unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void scale2x(void* void_dst, unsigned dst_slice, const void* void_src, unsigned src_slice, unsigned pixel, unsigned width, unsigned height)
{
	unsigned char* dst = (unsigned char*)void_dst;
	const unsigned char* src = (unsigned char*)void_src;
	unsigned count;

	assert(height >= 2);

	count = height;

	stage_scale2x(SCDST(0), SCDST(1), SCSRC(0), SCSRC(0), SCSRC(1), pixel, width);

	dst = SCDST(2);

	count -= 2;
	while (count) {
		stage_scale2x(SCDST(0), SCDST(1), SCSRC(0), SCSRC(1), SCSRC(2), pixel, width);

		dst = SCDST(2);
		src = SCSRC(1);

		--count;
	}

	stage_scale2x(SCDST(0), SCDST(1), SCSRC(1-1), SCSRC(2-1), SCSRC(2-1), pixel, width);

#if defined(__GNUC__) && defined(__i386__)
	scale2x_mmx_emms();
#endif
}