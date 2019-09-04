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
typedef  int v8i16 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVRL_B2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MUL4 (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B4_SB (int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST2x4_UB (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_SB2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNPCK_UB_SH (int /*<<< orphan*/ ,int,int) ; 
 int __msa_fill_h (int) ; 
 int* intra_pred_angle_low ; 

__attribute__((used)) static void hevc_intra_pred_angular_lower_32width_msa(const uint8_t *src_top,
                                                      const uint8_t *src_left,
                                                      uint8_t *dst,
                                                      int32_t stride,
                                                      int32_t mode)
{
    int16_t inv_angle[] = { -4096, -1638, -910, -630, -482, -390, -315 };
    int32_t h_cnt, v_cnt, idx0, fact_val0, idx1, fact_val1, tmp0;
    v16i8 top0, top1, dst_val0, top2, top3, dst_val1;
    v16i8 top4, top5, dst_val2, top6, top7, dst_val3;
    v8i16 fact0, fact1, fact2, fact3;
    v8i16 diff0, diff1, diff2, diff3, diff4, diff5, diff6, diff7;
    v8i16 diff8, diff9, diff10, diff11, diff12, diff13, diff14, diff15;
    int32_t angle, angle_loop, inv_angle_val, offset;
    uint8_t ref_array[3 * 32 + 4];
    uint8_t *ref_tmp = ref_array + 32;
    const uint8_t *ref, *src_top_tmp = src_top - 1;
    uint8_t *dst_org;
    int32_t last;

    angle = intra_pred_angle_low[mode - 2];
    last = angle;
    angle_loop = angle;

    ref = src_left - 1;
    if (last < -1) {
        inv_angle_val = inv_angle[mode - 11];

        LD_SB2(ref, 16, top0, top1);
        tmp0 = LW(ref + 32);
        ST_SB2(top0, top1, ref_tmp, 16);
        SW(tmp0, ref_tmp + 32);

        for (h_cnt = last; h_cnt <= -1; h_cnt++) {
            offset = (h_cnt * inv_angle_val + 128) >> 8;
            ref_tmp[h_cnt] = src_top_tmp[offset];
        }

        ref = ref_tmp;
    }

    for (v_cnt = 0; v_cnt < 16; v_cnt++) {
        dst_org = dst;
        idx0 = angle_loop >> 5;
        fact_val0 = angle_loop & 31;
        angle_loop += angle;

        idx1 = angle_loop >> 5;
        fact_val1 = angle_loop & 31;
        angle_loop += angle;

        top0 = LD_SB(ref + idx0 + 1);
        top4 = LD_SB(ref + idx1 + 1);
        top1 = LD_SB(ref + idx0 + 17);
        top5 = LD_SB(ref + idx1 + 17);
        top3 = LD_SB(ref + idx0 + 33);
        top7 = LD_SB(ref + idx1 + 33);

        fact0 = __msa_fill_h(fact_val0);
        fact1 = __msa_fill_h(32 - fact_val0);
        fact2 = __msa_fill_h(fact_val1);
        fact3 = __msa_fill_h(32 - fact_val1);

        top2 = top1;
        top6 = top5;

        SLDI_B2_SB(top1, top3, top0, top2, top1, top3, 1);
        SLDI_B2_SB(top5, top7, top4, top6, top5, top7, 1);

        UNPCK_UB_SH(top0, diff0, diff1);
        UNPCK_UB_SH(top1, diff2, diff3);
        UNPCK_UB_SH(top2, diff4, diff5);
        UNPCK_UB_SH(top3, diff6, diff7);
        UNPCK_UB_SH(top4, diff8, diff9);
        UNPCK_UB_SH(top5, diff10, diff11);
        UNPCK_UB_SH(top6, diff12, diff13);
        UNPCK_UB_SH(top7, diff14, diff15);

        MUL4(diff2, fact0, diff3, fact0, diff6, fact0, diff7, fact0,
             diff2, diff3, diff6, diff7);
        MUL4(diff10, fact2, diff11, fact2, diff14, fact2, diff15, fact2,
             diff10, diff11, diff14, diff15);

        diff2 += diff0 * fact1;
        diff3 += diff1 * fact1;
        diff6 += diff4 * fact1;
        diff7 += diff5 * fact1;
        diff10 += diff8 * fact3;
        diff11 += diff9 * fact3;
        diff14 += diff12 * fact3;
        diff15 += diff13 * fact3;

        SRARI_H4_SH(diff2, diff3, diff6, diff7, 5);
        SRARI_H4_SH(diff10, diff11, diff14, diff15, 5);
        PCKEV_B4_SB(diff3, diff2, diff7, diff6, diff11, diff10, diff15, diff14,
                    dst_val0, dst_val1, dst_val2, dst_val3);
        ILVRL_B2_SH(dst_val2, dst_val0, diff0, diff1);
        ILVRL_B2_SH(dst_val3, dst_val1, diff2, diff3);

        ST2x4_UB(diff0, 0, dst_org, stride);
        dst_org += (4 * stride);
        ST2x4_UB(diff0, 4, dst_org, stride);
        dst_org += (4 * stride);
        ST2x4_UB(diff1, 0, dst_org, stride);
        dst_org += (4 * stride);
        ST2x4_UB(diff1, 4, dst_org, stride);
        dst_org += (4 * stride);

        ST2x4_UB(diff2, 0, dst_org, stride);
        dst_org += (4 * stride);
        ST2x4_UB(diff2, 4, dst_org, stride);
        dst_org += (4 * stride);
        ST2x4_UB(diff3, 0, dst_org, stride);
        dst_org += (4 * stride);
        ST2x4_UB(diff3, 4, dst_org, stride);
        dst_org += (4 * stride);

        dst += 2;
    }
}