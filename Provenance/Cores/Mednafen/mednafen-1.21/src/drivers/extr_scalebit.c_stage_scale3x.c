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
 int /*<<< orphan*/  scale3x_16_def (void*,void*,void*,void const*,void const*,void const*,unsigned int) ; 
 int /*<<< orphan*/  scale3x_32_def (void*,void*,void*,void const*,void const*,void const*,unsigned int) ; 
 int /*<<< orphan*/  scale3x_8_def (void*,void*,void*,void const*,void const*,void const*,unsigned int) ; 

__attribute__((used)) static inline void stage_scale3x(void* dst0, void* dst1, void* dst2, const void* src0, const void* src1, const void* src2, unsigned pixel, unsigned pixel_per_row)
{
	switch (pixel) {
		case 1 : scale3x_8_def(dst0, dst1, dst2, src0, src1, src2, pixel_per_row); break;
		case 2 : scale3x_16_def(dst0, dst1, dst2, src0, src1, src2, pixel_per_row); break;
		case 4 : scale3x_32_def(dst0, dst1, dst2, src0, src1, src2, pixel_per_row); break;
	}
}