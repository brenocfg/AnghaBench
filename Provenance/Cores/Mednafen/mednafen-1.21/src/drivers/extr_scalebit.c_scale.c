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
 int /*<<< orphan*/  scale2x (void*,unsigned int,void const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scale3x (void*,unsigned int,void const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scale4x (void*,unsigned int,void const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

void scale(unsigned scale_factor, void* void_dst, unsigned dst_slice, const void* void_src, unsigned src_slice, unsigned pixel, unsigned width, unsigned height)
{
	switch (scale_factor) {
	case 2 :
		scale2x(void_dst, dst_slice, void_src, src_slice, pixel, width, height);
		break;
	case 3 :
		scale3x(void_dst, dst_slice, void_src, src_slice, pixel, width, height);
		break;
	case 4 :
		scale4x(void_dst, dst_slice, void_src, src_slice, pixel, width, height);
		break;
	}
}