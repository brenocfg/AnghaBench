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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_16multx8mult_msa (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void copy_width16_msa(const uint8_t *src, int32_t src_stride,
                             uint8_t *dst, int32_t dst_stride,
                             int32_t height)
{
    int32_t cnt;
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7;

    if (0 == height % 12) {
        for (cnt = (height / 12); cnt--;) {
            LD_UB8(src, src_stride,
                   src0, src1, src2, src3, src4, src5, src6, src7);
            src += (8 * src_stride);
            ST_UB8(src0, src1, src2, src3, src4, src5, src6, src7,
                   dst, dst_stride);
            dst += (8 * dst_stride);

            LD_UB4(src, src_stride, src0, src1, src2, src3);
            src += (4 * src_stride);
            ST_UB4(src0, src1, src2, src3, dst, dst_stride);
            dst += (4 * dst_stride);
        }
    } else if (0 == height % 8) {
        copy_16multx8mult_msa(src, src_stride, dst, dst_stride, height, 16);
    } else if (0 == height % 4) {
        for (cnt = (height >> 2); cnt--;) {
            LD_UB4(src, src_stride, src0, src1, src2, src3);
            src += (4 * src_stride);

            ST_UB4(src0, src1, src2, src3, dst, dst_stride);
            dst += (4 * dst_stride);
        }
    }
}