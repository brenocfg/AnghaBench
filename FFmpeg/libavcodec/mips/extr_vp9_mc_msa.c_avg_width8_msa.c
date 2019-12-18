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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVER_UB2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVER_UB4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ST_D8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void avg_width8_msa(const uint8_t *src, int32_t src_stride,
                           uint8_t *dst, int32_t dst_stride,
                           int32_t height)
{
    int32_t cnt;
    uint64_t tp0, tp1, tp2, tp3, tp4, tp5, tp6, tp7;
    v16u8 src0, src1, src2, src3;
    v16u8 dst0, dst1, dst2, dst3;

    if (0 == (height % 8)) {
        for (cnt = (height >> 3); cnt--;) {
            LD4(src, src_stride, tp0, tp1, tp2, tp3);
            src += 4 * src_stride;
            LD4(src, src_stride, tp4, tp5, tp6, tp7);
            src += 4 * src_stride;
            INSERT_D2_UB(tp0, tp1, src0);
            INSERT_D2_UB(tp2, tp3, src1);
            INSERT_D2_UB(tp4, tp5, src2);
            INSERT_D2_UB(tp6, tp7, src3);
            LD4(dst, dst_stride, tp0, tp1, tp2, tp3);
            LD4(dst + 4 * dst_stride, dst_stride, tp4, tp5, tp6, tp7);
            INSERT_D2_UB(tp0, tp1, dst0);
            INSERT_D2_UB(tp2, tp3, dst1);
            INSERT_D2_UB(tp4, tp5, dst2);
            INSERT_D2_UB(tp6, tp7, dst3);
            AVER_UB4_UB(src0, dst0, src1, dst1, src2, dst2, src3, dst3, dst0,
                        dst1, dst2, dst3);
            ST_D8(dst0, dst1, dst2, dst3, 0, 1, 0, 1, 0, 1, 0, 1, dst, dst_stride);
            dst += 8 * dst_stride;
        }
    } else if (4 == height) {
        LD4(src, src_stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, src0);
        INSERT_D2_UB(tp2, tp3, src1);
        LD4(dst, dst_stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, dst0);
        INSERT_D2_UB(tp2, tp3, dst1);
        AVER_UB2_UB(src0, dst0, src1, dst1, dst0, dst1);
        ST_D4(dst0, dst1, 0, 1, 0, 1, dst, dst_stride);
    }
}