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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVER_UB4_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void avg_width8_msa(const uint8_t *src, int32_t src_stride,
                           uint8_t *dst, int32_t dst_stride,
                           int32_t height)
{
    int32_t cnt;
    uint64_t out0, out1, out2, out3;
    v16u8 src0, src1, src2, src3;
    v16u8 dst0, dst1, dst2, dst3;

    for (cnt = (height / 4); cnt--;) {
        LD_UB4(src, src_stride, src0, src1, src2, src3);
        src += (4 * src_stride);
        LD_UB4(dst, dst_stride, dst0, dst1, dst2, dst3);

        AVER_UB4_UB(src0, dst0, src1, dst1, src2, dst2, src3, dst3,
                    dst0, dst1, dst2, dst3);

        out0 = __msa_copy_u_d((v2i64) dst0, 0);
        out1 = __msa_copy_u_d((v2i64) dst1, 0);
        out2 = __msa_copy_u_d((v2i64) dst2, 0);
        out3 = __msa_copy_u_d((v2i64) dst3, 0);
        SD4(out0, out1, out2, out3, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}