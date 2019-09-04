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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ST_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ff_vert_16x16_msa(uint8_t *dst, ptrdiff_t dst_stride, const uint8_t *left,
                       const uint8_t *src)
{
    uint32_t row;
    v16u8 src0;

    src0 = LD_UB(src);

    for (row = 16; row--;) {
        ST_UB(src0, dst);
        dst += dst_stride;
    }
}