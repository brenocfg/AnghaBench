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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ST_UB2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void intra_predict_vert_32x32_msa(const uint8_t *src, uint8_t *dst,
                                         int32_t dst_stride)
{
    uint32_t row;
    v16u8 src1, src2;

    src1 = LD_UB(src);
    src2 = LD_UB(src + 16);

    for (row = 32; row--;) {
        ST_UB2(src1, src2, dst, 16);
        dst += dst_stride;
    }
}