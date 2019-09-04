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
typedef  scalar_t__ v8i16 ;
typedef  scalar_t__ v4i32 ;
typedef  int uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_SH2_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DOTP_SH4_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPADD_SH2_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPADD_SH4_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HEVC_EVEN16_CALC (int*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ILVL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SW2 (int*,int,scalar_t__,scalar_t__) ; 
 int LW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SAT_SW2_SW (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SPLATI_W4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRAR_W2_SW (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_SH (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_SW2 (scalar_t__,scalar_t__,int*,int) ; 
 scalar_t__ __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_h (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * gt32x32_cnst0 ; 
 int /*<<< orphan*/ * gt32x32_cnst1 ; 
 int /*<<< orphan*/ * gt32x32_cnst2 ; 
 int /*<<< orphan*/ * gt8x8_cnst ; 

__attribute__((used)) static void hevc_idct_8x32_column_msa(int16_t *coeffs, uint8_t buf_pitch,
                                      uint8_t round)
{
    uint8_t i;
    const int16_t *filter_ptr0 = &gt32x32_cnst0[0];
    const int16_t *filter_ptr1 = &gt32x32_cnst1[0];
    const int16_t *filter_ptr2 = &gt32x32_cnst2[0];
    const int16_t *filter_ptr3 = &gt8x8_cnst[0];
    int16_t *src0 = (coeffs + buf_pitch);
    int16_t *src1 = (coeffs + 2 * buf_pitch);
    int16_t *src2 = (coeffs + 4 * buf_pitch);
    int16_t *src3 = (coeffs);
    int32_t cnst0, cnst1;
    int32_t tmp_buf[8 * 32 + 15];
    int32_t *tmp_buf_ptr = tmp_buf + 15;
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v8i16 src0_r, src1_r, src2_r, src3_r, src4_r, src5_r, src6_r, src7_r;
    v8i16 src0_l, src1_l, src2_l, src3_l, src4_l, src5_l, src6_l, src7_l;
    v8i16 filt0, filter0, filter1, filter2, filter3;
    v4i32 sum0_r, sum0_l, sum1_r, sum1_l, tmp0_r, tmp0_l, tmp1_r, tmp1_l;

    /* Align pointer to 64 byte boundary */
    tmp_buf_ptr = (int32_t *)(((uintptr_t) tmp_buf_ptr) & ~(uintptr_t) 63);

    /* process coeff 4, 12, 20, 28 */
    LD_SH4(src2, 8 * buf_pitch, in0, in1, in2, in3);
    ILVR_H2_SH(in1, in0, in3, in2, src0_r, src1_r);
    ILVL_H2_SH(in1, in0, in3, in2, src0_l, src1_l);

    LD_SH2(src3, 16 * buf_pitch, in4, in6);
    LD_SH2((src3 + 8 * buf_pitch), 16 * buf_pitch, in5, in7);
    ILVR_H2_SH(in6, in4, in7, in5, src2_r, src3_r);
    ILVL_H2_SH(in6, in4, in7, in5, src2_l, src3_l);

    /* loop for all columns of constants */
    for (i = 0; i < 2; i++) {
        /* processing single column of constants */
        cnst0 = LW(filter_ptr2);
        cnst1 = LW(filter_ptr2 + 2);

        filter0 = (v8i16) __msa_fill_w(cnst0);
        filter1 = (v8i16) __msa_fill_w(cnst1);

        DOTP_SH2_SW(src0_r, src0_l, filter0, filter0, sum0_r, sum0_l);
        DPADD_SH2_SW(src1_r, src1_l, filter1, filter1, sum0_r, sum0_l);
        ST_SW2(sum0_r, sum0_l, (tmp_buf_ptr + 2 * i * 8), 4);

        /* processing single column of constants */
        cnst0 = LW(filter_ptr2 + 4);
        cnst1 = LW(filter_ptr2 + 6);

        filter0 = (v8i16) __msa_fill_w(cnst0);
        filter1 = (v8i16) __msa_fill_w(cnst1);

        DOTP_SH2_SW(src0_r, src0_l, filter0, filter0, sum0_r, sum0_l);
        DPADD_SH2_SW(src1_r, src1_l, filter1, filter1, sum0_r, sum0_l);
        ST_SW2(sum0_r, sum0_l, (tmp_buf_ptr + (2 * i + 1) * 8), 4);

        filter_ptr2 += 8;
    }

    /* process coeff 0, 8, 16, 24 */
    /* loop for all columns of constants */
    for (i = 0; i < 2; i++) {
        /* processing first column of filter constants */
        cnst0 = LW(filter_ptr3);
        cnst1 = LW(filter_ptr3 + 2);

        filter0 = (v8i16) __msa_fill_w(cnst0);
        filter1 = (v8i16) __msa_fill_w(cnst1);

        DOTP_SH4_SW(src2_r, src2_l, src3_r, src3_l, filter0, filter0, filter1,
                    filter1, sum0_r, sum0_l, tmp1_r, tmp1_l);

        sum1_r = sum0_r - tmp1_r;
        sum1_l = sum0_l - tmp1_l;
        sum0_r = sum0_r + tmp1_r;
        sum0_l = sum0_l + tmp1_l;

        HEVC_EVEN16_CALC(tmp_buf_ptr, sum0_r, sum0_l, i, (7 - i));
        HEVC_EVEN16_CALC(tmp_buf_ptr, sum1_r, sum1_l, (3 - i), (4 + i));

        filter_ptr3 += 8;
    }

    /* process coeff 2 6 10 14 18 22 26 30 */
    LD_SH8(src1, 4 * buf_pitch, in0, in1, in2, in3, in4, in5, in6, in7);
    ILVR_H4_SH(in1, in0, in3, in2, in5, in4, in7, in6,
               src0_r, src1_r, src2_r, src3_r);
    ILVL_H4_SH(in1, in0, in3, in2, in5, in4, in7, in6,
               src0_l, src1_l, src2_l, src3_l);

    /* loop for all columns of constants */
    for (i = 0; i < 8; i++) {
        /* processing single column of constants */
        filt0 = LD_SH(filter_ptr1);
        SPLATI_W4_SH(filt0, filter0, filter1, filter2, filter3);
        DOTP_SH2_SW(src0_r, src0_l, filter0, filter0, sum0_r, sum0_l);
        DPADD_SH4_SW(src1_r, src1_l, src2_r, src2_l, filter1, filter1, filter2,
                     filter2, sum0_r, sum0_l, sum0_r, sum0_l);
        DPADD_SH2_SW(src3_r, src3_l, filter3, filter3, sum0_r, sum0_l);

        LD_SW2(tmp_buf_ptr + i * 8, 4, tmp0_r, tmp0_l);
        tmp1_r = tmp0_r;
        tmp1_l = tmp0_l;
        tmp0_r += sum0_r;
        tmp0_l += sum0_l;
        ST_SW2(tmp0_r, tmp0_l, (tmp_buf_ptr + i * 8), 4);
        tmp1_r -= sum0_r;
        tmp1_l -= sum0_l;
        ST_SW2(tmp1_r, tmp1_l, (tmp_buf_ptr + (15 - i) * 8), 4);

        filter_ptr1 += 8;
    }

    /* process coeff 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 */
    LD_SH8(src0, 2 * buf_pitch, in0, in1, in2, in3, in4, in5, in6, in7);
    src0 += 16 * buf_pitch;
    ILVR_H4_SH(in1, in0, in3, in2, in5, in4, in7, in6,
               src0_r, src1_r, src2_r, src3_r);
    ILVL_H4_SH(in1, in0, in3, in2, in5, in4, in7, in6,
               src0_l, src1_l, src2_l, src3_l);

    LD_SH8(src0, 2 * buf_pitch, in0, in1, in2, in3, in4, in5, in6, in7);
    ILVR_H4_SH(in1, in0, in3, in2, in5, in4, in7, in6,
               src4_r, src5_r, src6_r, src7_r);
    ILVL_H4_SH(in1, in0, in3, in2, in5, in4, in7, in6,
               src4_l, src5_l, src6_l, src7_l);

    /* loop for all columns of filter constants */
    for (i = 0; i < 16; i++) {
        /* processing single column of constants */
        filt0 = LD_SH(filter_ptr0);
        SPLATI_W4_SH(filt0, filter0, filter1, filter2, filter3);
        DOTP_SH2_SW(src0_r, src0_l, filter0, filter0, sum0_r, sum0_l);
        DPADD_SH4_SW(src1_r, src1_l, src2_r, src2_l, filter1, filter1, filter2,
                     filter2, sum0_r, sum0_l, sum0_r, sum0_l);
        DPADD_SH2_SW(src3_r, src3_l, filter3, filter3, sum0_r, sum0_l);

        tmp1_r = sum0_r;
        tmp1_l = sum0_l;

        filt0 = LD_SH(filter_ptr0 + 8);
        SPLATI_W4_SH(filt0, filter0, filter1, filter2, filter3);
        DOTP_SH2_SW(src4_r, src4_l, filter0, filter0, sum0_r, sum0_l);
        DPADD_SH4_SW(src5_r, src5_l, src6_r, src6_l, filter1, filter1, filter2,
                     filter2, sum0_r, sum0_l, sum0_r, sum0_l);
        DPADD_SH2_SW(src7_r, src7_l, filter3, filter3, sum0_r, sum0_l);

        sum0_r += tmp1_r;
        sum0_l += tmp1_l;

        LD_SW2(tmp_buf_ptr + i * 8, 4, tmp0_r, tmp0_l);
        tmp1_r = tmp0_r;
        tmp1_l = tmp0_l;
        tmp0_r += sum0_r;
        tmp0_l += sum0_l;
        sum1_r = __msa_fill_w(round);
        SRAR_W2_SW(tmp0_r, tmp0_l, sum1_r);
        SAT_SW2_SW(tmp0_r, tmp0_l, 15);
        in0 = __msa_pckev_h((v8i16) tmp0_l, (v8i16) tmp0_r);
        ST_SH(in0, (coeffs + i * buf_pitch));
        tmp1_r -= sum0_r;
        tmp1_l -= sum0_l;
        SRAR_W2_SW(tmp1_r, tmp1_l, sum1_r);
        SAT_SW2_SW(tmp1_r, tmp1_l, 15);
        in0 = __msa_pckev_h((v8i16) tmp1_l, (v8i16) tmp1_r);
        ST_SH(in0, (coeffs + (31 - i) * buf_pitch));

        filter_ptr0 += 16;
    }
}