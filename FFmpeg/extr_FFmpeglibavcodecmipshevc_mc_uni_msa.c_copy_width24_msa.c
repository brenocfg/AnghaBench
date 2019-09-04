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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_width24_msa(uint8_t *src, int32_t src_stride,
                             uint8_t *dst, int32_t dst_stride,
                             int32_t height)
{
    int32_t cnt;
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7;
    uint64_t out0, out1, out2, out3, out4, out5, out6, out7;

    for (cnt = 4; cnt--;) {
        LD_UB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
        LD4(src + 16, src_stride, out0, out1, out2, out3);
        src += (4 * src_stride);
        LD4(src + 16, src_stride, out4, out5, out6, out7);
        src += (4 * src_stride);

        ST_UB8(src0, src1, src2, src3, src4, src5, src6, src7, dst, dst_stride);
        SD4(out0, out1, out2, out3, dst + 16, dst_stride);
        dst += (4 * dst_stride);
        SD4(out4, out5, out6, out7, dst + 16, dst_stride);
        dst += (4 * dst_stride);
    }
}