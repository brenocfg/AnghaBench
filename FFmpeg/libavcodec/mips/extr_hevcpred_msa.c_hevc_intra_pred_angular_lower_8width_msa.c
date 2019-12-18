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
 int /*<<< orphan*/  ILVRL_H2_SH (int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_B2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/  const*) ; 
 int LW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MUL4 (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B4_SB (int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B4_SH (int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST_W8 (int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNPCK_UB_SH (int /*<<< orphan*/ ,int,int) ; 
 int __msa_fill_h (int) ; 
 int* intra_pred_angle_low ; 

__attribute__((used)) static void hevc_intra_pred_angular_lower_8width_msa(const uint8_t *src_top,
                                                     const uint8_t *src_left,
                                                     uint8_t *dst,
                                                     int32_t stride,
                                                     int32_t mode)
{
    int16_t inv_angle[] = { -4096, -1638, -910, -630, -482, -390, -315 };
    uint8_t ref_array[3 * 32 + 4];
    uint8_t *ref_tmp = ref_array + 8;
    const uint8_t *ref;
    const uint8_t *src_top_tmp = src_top - 1;
    uint8_t *dst_org;
    int32_t last, offset, tmp0, tmp1, tmp2;
    int32_t h_cnt, v_cnt, idx0, fact_val0, idx1, fact_val1;
    int32_t idx2, fact_val2, idx3, fact_val3;
    int32_t angle, angle_loop, inv_angle_val;
    v16i8 top0, top1, top2, top3;
    v16i8 dst_val0, dst_val1, dst_val2, dst_val3;
    v8i16 diff0, diff1, diff2, diff3, diff4, diff5, diff6, diff7;
    v8i16 fact0, fact1, fact2, fact3, fact4, fact5, fact6, fact7;

    angle = intra_pred_angle_low[mode - 2];
    last = (angle) >> 2;
    angle_loop = angle;

    ref = src_left - 1;
    if (last < -1) {
        inv_angle_val = inv_angle[mode - 11];

        tmp0 = LW(ref);
        tmp1 = LW(ref + 4);
        tmp2 = LW(ref + 8);
        SW(tmp0, ref_tmp);
        SW(tmp1, ref_tmp + 4);
        SW(tmp2, ref_tmp + 8);

        for (h_cnt = last; h_cnt <= -1; h_cnt++) {
            offset = (h_cnt * inv_angle_val + 128) >> 8;
            ref_tmp[h_cnt] = src_top_tmp[offset];
        }

        ref = ref_tmp;
    }

    for (v_cnt = 0; v_cnt < 2; v_cnt++) {
        dst_org = dst;

        idx0 = angle_loop >> 5;
        fact_val0 = angle_loop & 31;
        angle_loop += angle;

        idx1 = angle_loop >> 5;
        fact_val1 = angle_loop & 31;
        angle_loop += angle;

        idx2 = angle_loop >> 5;
        fact_val2 = angle_loop & 31;
        angle_loop += angle;

        idx3 = angle_loop >> 5;
        fact_val3 = angle_loop & 31;
        angle_loop += angle;

        top0 = LD_SB(ref + idx0 + 1);
        top1 = LD_SB(ref + idx1 + 1);
        top2 = LD_SB(ref + idx2 + 1);
        top3 = LD_SB(ref + idx3 + 1);

        fact0 = __msa_fill_h(fact_val0);
        fact1 = __msa_fill_h(32 - fact_val0);
        fact2 = __msa_fill_h(fact_val1);
        fact3 = __msa_fill_h(32 - fact_val1);
        fact4 = __msa_fill_h(fact_val2);
        fact5 = __msa_fill_h(32 - fact_val2);
        fact6 = __msa_fill_h(fact_val3);
        fact7 = __msa_fill_h(32 - fact_val3);

        UNPCK_UB_SH(top0, diff0, diff1);
        UNPCK_UB_SH(top1, diff2, diff3);
        UNPCK_UB_SH(top2, diff4, diff5);
        UNPCK_UB_SH(top3, diff6, diff7);
        SLDI_B4_SH(diff1, diff0, diff3, diff2, diff5, diff4, diff7, diff6, 2,
                   diff1, diff3, diff5, diff7);
        MUL4(diff1, fact0, diff3, fact2, diff5, fact4, diff7, fact6,
             diff1, diff3, diff5, diff7);

        diff1 += diff0 * fact1;
        diff3 += diff2 * fact3;
        diff5 += diff4 * fact5;
        diff7 += diff6 * fact7;

        SRARI_H4_SH(diff1, diff3, diff5, diff7, 5);
        PCKEV_B4_SB(diff1, diff1, diff3, diff3, diff5, diff5, diff7, diff7,
                    dst_val0, dst_val1, dst_val2, dst_val3);
        ILVR_B2_SH(dst_val1, dst_val0, dst_val3, dst_val2, diff0, diff1);
        ILVRL_H2_SH(diff1, diff0, diff3, diff4);
        ST_W8(diff3, diff4, 0, 1, 2, 3, 0, 1, 2, 3, dst_org, stride);
        dst += 4;
    }
}