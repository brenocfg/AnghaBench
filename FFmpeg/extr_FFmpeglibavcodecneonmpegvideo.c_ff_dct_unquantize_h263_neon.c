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
typedef  int /*<<< orphan*/  uint16x8_t ;
typedef  int /*<<< orphan*/  uint16x4_t ;
typedef  int /*<<< orphan*/  int16x8_t ;
typedef  int /*<<< orphan*/  int16x4_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  vadd_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaddq_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbsl_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbslq_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vceq_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vceqq_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vclt_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcltq_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdup_n_s16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdupq_n_s16 (int) ; 
 int /*<<< orphan*/  vget_high_s16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vld1_s16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vld1q_s16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmul_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmulq_s16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnegq_s16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vreinterpret_s16_u16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vreinterpret_u16_s16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vreinterpretq_s16_u16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vreinterpretq_u16_s16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vst1_s16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vst1q_s16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline ff_dct_unquantize_h263_neon(int qscale, int qadd, int nCoeffs,
                                               int16_t *block)
{
    int16x8_t q0s16, q2s16, q3s16, q8s16, q10s16, q11s16, q13s16;
    int16x8_t q14s16, q15s16, qzs16;
    int16x4_t d0s16, d2s16, d3s16, dzs16;
    uint16x8_t q1u16, q9u16;
    uint16x4_t d1u16;

    dzs16 = vdup_n_s16(0);
    qzs16 = vdupq_n_s16(0);

    q15s16 = vdupq_n_s16(qscale << 1);
    q14s16 = vdupq_n_s16(qadd);
    q13s16 = vnegq_s16(q14s16);

    if (nCoeffs > 4) {
        for (; nCoeffs > 8; nCoeffs -= 16, block += 16) {
            q0s16 = vld1q_s16(block);
            q3s16 = vreinterpretq_s16_u16(vcltq_s16(q0s16, qzs16));
            q8s16 = vld1q_s16(block + 8);
            q1u16 = vceqq_s16(q0s16, qzs16);
            q2s16 = vmulq_s16(q0s16, q15s16);
            q11s16 = vreinterpretq_s16_u16(vcltq_s16(q8s16, qzs16));
            q10s16 = vmulq_s16(q8s16, q15s16);
            q3s16 = vbslq_s16(vreinterpretq_u16_s16(q3s16), q13s16, q14s16);
            q11s16 = vbslq_s16(vreinterpretq_u16_s16(q11s16), q13s16, q14s16);
            q2s16 = vaddq_s16(q2s16, q3s16);
            q9u16 = vceqq_s16(q8s16, qzs16);
            q10s16 = vaddq_s16(q10s16, q11s16);
            q0s16 = vbslq_s16(q1u16, q0s16, q2s16);
            q8s16 = vbslq_s16(q9u16, q8s16, q10s16);
            vst1q_s16(block, q0s16);
            vst1q_s16(block + 8, q8s16);
        }
    }
    if (nCoeffs <= 0)
        return;

    d0s16 = vld1_s16(block);
    d3s16 = vreinterpret_s16_u16(vclt_s16(d0s16, dzs16));
    d1u16 = vceq_s16(d0s16, dzs16);
    d2s16 = vmul_s16(d0s16, vget_high_s16(q15s16));
    d3s16 = vbsl_s16(vreinterpret_u16_s16(d3s16),
                     vget_high_s16(q13s16), vget_high_s16(q14s16));
    d2s16 = vadd_s16(d2s16, d3s16);
    d0s16 = vbsl_s16(d1u16, d0s16, d2s16);
    vst1_s16(block, d0s16);
}