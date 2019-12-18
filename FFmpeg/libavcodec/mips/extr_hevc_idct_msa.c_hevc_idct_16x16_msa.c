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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_IDCT16x16_COL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILVL_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH16 (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH8 (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_SH8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  TRANSPOSE8x8_SH_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* gt16x16_cnst ; 

__attribute__((used)) static void hevc_idct_16x16_msa(int16_t *coeffs)
{
    int16_t i, j, k;
    int16_t buf[256];
    int16_t *buf_ptr = &buf[0];
    int16_t *src = coeffs;
    const int16_t *filter = &gt16x16_cnst[0];
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v8i16 in8, in9, in10, in11, in12, in13, in14, in15;
    v8i16 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8i16 src0_r, src1_r, src2_r, src3_r, src4_r, src5_r, src6_r, src7_r;
    v8i16 src0_l, src1_l, src2_l, src3_l, src4_l, src5_l, src6_l, src7_l;

    for (i = 2; i--;) {
        LD_SH16(src, 16, in0, in1, in2, in3, in4, in5, in6, in7,
                in8, in9, in10, in11, in12, in13, in14, in15);

        ILVR_H4_SH(in4, in0, in12, in8, in6, in2, in14, in10,
                   src0_r, src1_r, src2_r, src3_r);
        ILVR_H4_SH(in5, in1, in13, in9, in3, in7, in11, in15,
                   src4_r, src5_r, src6_r, src7_r);
        ILVL_H4_SH(in4, in0, in12, in8, in6, in2, in14, in10,
                   src0_l, src1_l, src2_l, src3_l);
        ILVL_H4_SH(in5, in1, in13, in9, in3, in7, in11, in15,
                   src4_l, src5_l, src6_l, src7_l);
        HEVC_IDCT16x16_COL(src0_r, src1_r, src2_r, src3_r, src4_r, src5_r,
                           src6_r, src7_r, src0_l, src1_l, src2_l, src3_l,
                           src4_l, src5_l, src6_l, src7_l, 7);

        src += 8;
        buf_ptr = (&buf[0] + 8);
        filter = &gt16x16_cnst[0];
    }

    src = &buf[0];
    buf_ptr = coeffs;
    filter = &gt16x16_cnst[0];

    for (i = 2; i--;) {
        LD_SH16(src, 8, in0, in8, in1, in9, in2, in10, in3, in11,
                in4, in12, in5, in13, in6, in14, in7, in15);
        TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                           in0, in1, in2, in3, in4, in5, in6, in7);
        TRANSPOSE8x8_SH_SH(in8, in9, in10, in11, in12, in13, in14, in15,
                           in8, in9, in10, in11, in12, in13, in14, in15);
        ILVR_H4_SH(in4, in0, in12, in8, in6, in2, in14, in10,
                   src0_r, src1_r, src2_r, src3_r);
        ILVR_H4_SH(in5, in1, in13, in9, in3, in7, in11, in15,
                   src4_r, src5_r, src6_r, src7_r);
        ILVL_H4_SH(in4, in0, in12, in8, in6, in2, in14, in10,
                   src0_l, src1_l, src2_l, src3_l);
        ILVL_H4_SH(in5, in1, in13, in9, in3, in7, in11, in15,
                   src4_l, src5_l, src6_l, src7_l);
        HEVC_IDCT16x16_COL(src0_r, src1_r, src2_r, src3_r, src4_r, src5_r,
                           src6_r, src7_r, src0_l, src1_l, src2_l, src3_l,
                           src4_l, src5_l, src6_l, src7_l, 12);

        src += 128;
        buf_ptr = coeffs + 8;
        filter = &gt16x16_cnst[0];
    }

    LD_SH8(coeffs, 16, in0, in1, in2, in3, in4, in5, in6, in7);
    TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7);
    ST_SH8(vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, coeffs, 16);

    LD_SH8((coeffs + 8), 16, in0, in1, in2, in3, in4, in5, in6, in7);
    TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7);
    LD_SH8((coeffs + 128), 16, in8, in9, in10, in11, in12, in13, in14, in15);
    ST_SH8(vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, (coeffs + 128), 16);
    TRANSPOSE8x8_SH_SH(in8, in9, in10, in11, in12, in13, in14, in15,
                       vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7);
    ST_SH8(vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, (coeffs + 8), 16);

    LD_SH8((coeffs + 136), 16, in0, in1, in2, in3, in4, in5, in6, in7);
    TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7);
    ST_SH8(vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, (coeffs + 136), 16);
}