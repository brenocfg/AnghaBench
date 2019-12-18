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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ __msa_adds_s_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_bmnz_v (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_bmz_v (scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_clti_s_h (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_fill_h (size_t) ; 
 int __msa_hsub_u_h (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ilvr_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_subsus_u_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_xori_b (scalar_t__,int) ; 
 size_t* h263_loop_filter_strength_msa ; 

__attribute__((used)) static void h263_v_loop_filter_msa(uint8_t *src, int32_t stride, int32_t qscale)
{
    int32_t strength = h263_loop_filter_strength_msa[qscale];
    uint64_t res0, res1, res2, res3;
    v16u8 in0, in1, in2, in3;
    v8i16 temp0, temp2, diff0, diff2, diff4, diff6, diff8;
    v8i16 d0, a_d0, str_x2, str;

    src -= 2 * stride;
    LD_UB4(src, stride, in0, in3, in2, in1);
    temp0 = (v8i16) __msa_ilvr_b((v16i8) in0, (v16i8) in1);
    a_d0 = __msa_hsub_u_h((v16u8) temp0, (v16u8) temp0);
    temp2 = (v8i16) __msa_ilvr_b((v16i8) in2, (v16i8) in3);
    temp2 = __msa_hsub_u_h((v16u8) temp2, (v16u8) temp2);
    temp2 <<= 2;
    diff0 = a_d0 + temp2;
    diff2 = -(-diff0 >> 3);
    str_x2 = __msa_fill_h(-(strength << 1));
    temp0 = (str_x2 <= diff2);
    diff2 = (v8i16) __msa_bmz_v((v16u8) diff2, (v16u8) temp0, (v16u8) temp0);
    temp2 = str_x2 - diff2;
    str = __msa_fill_h(-strength);
    temp0 = (diff2 < str);
    diff2 = (v8i16) __msa_bmnz_v((v16u8) diff2, (v16u8) temp2, (v16u8) temp0);
    diff4 = diff0 >> 3;
    str_x2 = __msa_fill_h(strength << 1);
    temp0 = (diff4 <= str_x2);
    diff4 = (v8i16) __msa_bmz_v((v16u8) diff4, (v16u8) temp0, (v16u8) temp0);
    temp2 = str_x2 - diff4;
    str = __msa_fill_h(strength);
    temp0 = (str < diff4);
    diff4 = (v8i16) __msa_bmnz_v((v16u8) diff4, (v16u8) temp2, (v16u8) temp0);
    temp0 = __msa_clti_s_h(diff0, 0);
    d0 = (v8i16) __msa_bmnz_v((v16u8) diff4, (v16u8) diff2, (v16u8) temp0);
    diff2 = -diff2 >> 1;
    diff4 >>= 1;
    diff8 = (v8i16) __msa_bmnz_v((v16u8) diff4, (v16u8) diff2, (v16u8) temp0);
    diff6 = (-a_d0) >> 2;
    diff6 = -(diff6);
    temp2 = -diff8;
    temp0 = (diff6 < temp2);
    diff6 = (v8i16) __msa_bmnz_v((v16u8) diff6, (v16u8) temp2, (v16u8) temp0);
    diff2 = a_d0 >> 2;
    temp0 = (diff2 <= diff8);
    diff2 = (v8i16) __msa_bmz_v((v16u8) diff2, (v16u8) diff8, (v16u8) temp0);
    temp0 = __msa_clti_s_h(a_d0, 0);
    diff6 = (v8i16) __msa_bmz_v((v16u8) diff6, (v16u8) diff2, (v16u8) temp0);
    PCKEV_B2_SH(a_d0, diff6, a_d0, d0, diff6, d0);
    in0 = (v16u8) ((v16i8) in0 - (v16i8) diff6);
    in1 = (v16u8) ((v16i8) in1 + (v16i8) diff6);
    in3 = __msa_xori_b(in3, 128);
    in3 = (v16u8) __msa_adds_s_b((v16i8) in3, (v16i8) d0);
    in3 = __msa_xori_b(in3, 128);
    in2 = __msa_subsus_u_b(in2, (v16i8) d0);
    res0 = __msa_copy_u_d((v2i64) in0, 0);
    res1 = __msa_copy_u_d((v2i64) in3, 0);
    res2 = __msa_copy_u_d((v2i64) in2, 0);
    res3 = __msa_copy_u_d((v2i64) in1, 0);
    SD4(res0, res1, res2, res3, src, stride);
}