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
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_ST8x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B4_0_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void common_hz_bil_no_rnd_8x8_msa(const uint8_t *src, int32_t src_stride,
                                         uint8_t *dst, int32_t dst_stride)
{
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 src0_sld1, src1_sld1, src2_sld1, src3_sld1;
    v16i8 src4_sld1, src5_sld1, src6_sld1, src7_sld1;

    LD_SB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * src_stride);

    SLDI_B4_0_SB(src0, src1, src2, src3,
                 src0_sld1, src1_sld1, src2_sld1, src3_sld1, 1);
    SLDI_B4_0_SB(src4, src5, src6, src7,
                 src4_sld1, src5_sld1, src6_sld1, src7_sld1, 1);

    AVE_ST8x4_UB(src0, src0_sld1, src1, src1_sld1,
                 src2, src2_sld1, src3, src3_sld1, dst, dst_stride);
    dst += (4 * dst_stride);
    AVE_ST8x4_UB(src4, src4_sld1, src5, src5_sld1,
                 src6, src6_sld1, src7, src7_sld1, dst, dst_stride);
}