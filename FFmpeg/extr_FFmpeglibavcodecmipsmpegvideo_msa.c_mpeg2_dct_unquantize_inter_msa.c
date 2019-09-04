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
typedef  int v4i32 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  const int16_t ;

/* Variables and functions */
 scalar_t__ HADD_SW_S32 (int) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/  const*,int,int,int,int,int) ; 
 int /*<<< orphan*/  ST_SH (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  UNPCK_SH_SW (int,int,int) ; 
 scalar_t__ __msa_bmnz_v (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_ceqi_h (int,int /*<<< orphan*/ ) ; 
 int __msa_clti_s_h (int,int /*<<< orphan*/ ) ; 
 int __msa_fill_h (int) ; 
 int __msa_hadd_s_w (int,int) ; 
 int __msa_pckev_h (int,int) ; 

__attribute__((used)) static int32_t mpeg2_dct_unquantize_inter_msa(int16_t *block,
                                              int32_t qscale,
                                              const int16_t *quant_matrix)
{
    int32_t cnt, sum_res = -1;
    v8i16 block_vec, block_neg, qscale_vec, mask;
    v8i16 block_org0, block_org1, block_org2, block_org3;
    v8i16 quant_m0, quant_m1, quant_m2, quant_m3;
    v8i16 sum, mul, zero_mask;
    v4i32 mul_vec, qscale_l, qscale_r, quant_m_r, quant_m_l;
    v4i32 block_l, block_r, sad;

    qscale_vec = __msa_fill_h(qscale);
    for (cnt = 0; cnt < 2; cnt++) {
        LD_SH4(block, 8, block_org0, block_org1, block_org2, block_org3);
        LD_SH4(quant_matrix, 8, quant_m0, quant_m1, quant_m2, quant_m3);
        mask = __msa_clti_s_h(block_org0, 0);
        zero_mask = __msa_ceqi_h(block_org0, 0);
        block_neg = -block_org0;
        block_vec = (v8i16) __msa_bmnz_v((v16u8) block_org0, (v16u8) block_neg,
                                         (v16u8) mask);
        block_vec <<= 1;
        block_vec += 1;
        UNPCK_SH_SW(block_vec, block_r, block_l);
        UNPCK_SH_SW(qscale_vec, qscale_r, qscale_l);
        UNPCK_SH_SW(quant_m0, quant_m_r, quant_m_l);
        mul_vec = block_l * qscale_l;
        mul_vec *= quant_m_l;
        block_l = mul_vec >> 4;
        mul_vec = block_r * qscale_r;
        mul_vec *= quant_m_r;
        block_r = mul_vec >> 4;
        mul = (v8i16) __msa_pckev_h((v8i16) block_l, (v8i16) block_r);
        block_neg = - mul;
        sum = (v8i16) __msa_bmnz_v((v16u8) mul, (v16u8) block_neg,
                                   (v16u8) mask);
        sum = (v8i16) __msa_bmnz_v((v16u8) sum, (v16u8) block_org0,
                                   (v16u8) zero_mask);
        ST_SH(sum, block);
        block += 8;
        quant_matrix += 8;
        sad = __msa_hadd_s_w(sum, sum);
        sum_res += HADD_SW_S32(sad);
        mask = __msa_clti_s_h(block_org1, 0);
        zero_mask = __msa_ceqi_h(block_org1, 0);
        block_neg = - block_org1;
        block_vec = (v8i16) __msa_bmnz_v((v16u8) block_org1, (v16u8) block_neg,
                                         (v16u8) mask);
        block_vec <<= 1;
        block_vec += 1;
        UNPCK_SH_SW(block_vec, block_r, block_l);
        UNPCK_SH_SW(qscale_vec, qscale_r, qscale_l);
        UNPCK_SH_SW(quant_m1, quant_m_r, quant_m_l);
        mul_vec = block_l * qscale_l;
        mul_vec *= quant_m_l;
        block_l = mul_vec >> 4;
        mul_vec = block_r * qscale_r;
        mul_vec *= quant_m_r;
        block_r = mul_vec >> 4;
        mul = __msa_pckev_h((v8i16) block_l, (v8i16) block_r);
        block_neg = - mul;
        sum = (v8i16) __msa_bmnz_v((v16u8) mul, (v16u8) block_neg,
                                   (v16u8) mask);
        sum = (v8i16) __msa_bmnz_v((v16u8) sum, (v16u8) block_org1,
                                   (v16u8) zero_mask);
        ST_SH(sum, block);

        block += 8;
        quant_matrix += 8;
        sad = __msa_hadd_s_w(sum, sum);
        sum_res += HADD_SW_S32(sad);
        mask = __msa_clti_s_h(block_org2, 0);
        zero_mask = __msa_ceqi_h(block_org2, 0);
        block_neg = - block_org2;
        block_vec = (v8i16) __msa_bmnz_v((v16u8) block_org2, (v16u8) block_neg,
                                         (v16u8) mask);
        block_vec <<= 1;
        block_vec += 1;
        UNPCK_SH_SW(block_vec, block_r, block_l);
        UNPCK_SH_SW(qscale_vec, qscale_r, qscale_l);
        UNPCK_SH_SW(quant_m2, quant_m_r, quant_m_l);
        mul_vec = block_l * qscale_l;
        mul_vec *= quant_m_l;
        block_l = mul_vec >> 4;
        mul_vec = block_r * qscale_r;
        mul_vec *= quant_m_r;
        block_r = mul_vec >> 4;
        mul = __msa_pckev_h((v8i16) block_l, (v8i16) block_r);
        block_neg = - mul;
        sum = (v8i16) __msa_bmnz_v((v16u8) mul, (v16u8) block_neg,
                                   (v16u8) mask);
        sum = (v8i16) __msa_bmnz_v((v16u8) sum, (v16u8) block_org2,
                                   (v16u8) zero_mask);
        ST_SH(sum, block);

        block += 8;
        quant_matrix += 8;
        sad = __msa_hadd_s_w(sum, sum);
        sum_res += HADD_SW_S32(sad);
        mask = __msa_clti_s_h(block_org3, 0);
        zero_mask = __msa_ceqi_h(block_org3, 0);
        block_neg = - block_org3;
        block_vec = (v8i16) __msa_bmnz_v((v16u8) block_org3, (v16u8) block_neg,
                                         (v16u8) mask);
        block_vec <<= 1;
        block_vec += 1;
        UNPCK_SH_SW(block_vec, block_r, block_l);
        UNPCK_SH_SW(qscale_vec, qscale_r, qscale_l);
        UNPCK_SH_SW(quant_m3, quant_m_r, quant_m_l);
        mul_vec = block_l * qscale_l;
        mul_vec *= quant_m_l;
        block_l = mul_vec >> 4;
        mul_vec = block_r * qscale_r;
        mul_vec *= quant_m_r;
        block_r = mul_vec >> 4;
        mul = __msa_pckev_h((v8i16) block_l, (v8i16) block_r);
        block_neg = - mul;
        sum = (v8i16) __msa_bmnz_v((v16u8) mul, (v16u8) block_neg,
                                   (v16u8) mask);
        sum = (v8i16) __msa_bmnz_v((v16u8) sum, (v16u8) block_org3,
                                   (v16u8) zero_mask);
        ST_SH(sum, block);

        block += 8;
        quant_matrix += 8;
        sad = __msa_hadd_s_w(sum, sum);
        sum_res += HADD_SW_S32(sad);
    }

    return sum_res;
}