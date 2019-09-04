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
typedef  int /*<<< orphan*/  v4i32 ;
typedef  scalar_t__ v16u8 ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVER_UB2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_UB (int const*) ; 
 int /*<<< orphan*/  LD_UB2 (int const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  __msa_copy_u_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void common_vt_bil_4w_msa(const uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 uint8_t height)
{
    uint8_t loop_cnt;
    uint32_t out0, out1;
    v16u8 src0, src1, src2, res0, res1;

    src0 = LD_UB(src);
    src += src_stride;

    for (loop_cnt = (height >> 1); loop_cnt--;) {
        LD_UB2(src, src_stride, src1, src2);
        src += (2 * src_stride);

        AVER_UB2_UB(src0, src1, src1, src2, res0, res1);

        out0 = __msa_copy_u_w((v4i32) res0, 0);
        out1 = __msa_copy_u_w((v4i32) res1, 0);
        SW(out0, dst);
        dst += dst_stride;
        SW(out1, dst);
        dst += dst_stride;

        src0 = src2;
    }
}