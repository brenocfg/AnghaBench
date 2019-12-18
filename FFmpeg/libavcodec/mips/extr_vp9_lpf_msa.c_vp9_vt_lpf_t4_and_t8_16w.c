#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8u16 ;
typedef  scalar_t__ v8i16 ;
typedef  scalar_t__ v16u8 ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_B4_UH (TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B8_UH (TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_UB (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_UB2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W8 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP9_FILTER8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP9_FLAT4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP9_LPF_FILTER4_4W (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_bmnz_v (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int) ; 
 scalar_t__ __msa_test_bz_v (scalar_t__) ; 

__attribute__((used)) static int32_t vp9_vt_lpf_t4_and_t8_16w(uint8_t *src, uint8_t *filter48,
                                        uint8_t *src_org, ptrdiff_t pitch,
                                        int32_t b_limit_ptr,
                                        int32_t limit_ptr,
                                        int32_t thresh_ptr)
{
    v16u8 p3, p2, p1, p0, q3, q2, q1, q0;
    v16u8 p2_out, p1_out, p0_out, q0_out, q1_out, q2_out;
    v16u8 flat, mask, hev, thresh, b_limit, limit;
    v8u16 p3_r, p2_r, p1_r, p0_r, q0_r, q1_r, q2_r, q3_r;
    v8u16 p3_l, p2_l, p1_l, p0_l, q0_l, q1_l, q2_l, q3_l;
    v8i16 p2_filt8_r, p1_filt8_r, p0_filt8_r;
    v8i16 q0_filt8_r, q1_filt8_r, q2_filt8_r;
    v8i16 p2_filt8_l, p1_filt8_l, p0_filt8_l;
    v8i16 q0_filt8_l, q1_filt8_l, q2_filt8_l;
    v16i8 zero = { 0 };
    v8i16 vec0, vec1, vec2, vec3, vec4, vec5;

    /* load vector elements */
    LD_UB8(src - (4 * 16), 16, p3, p2, p1, p0, q0, q1, q2, q3);

    thresh = (v16u8) __msa_fill_b(thresh_ptr);
    b_limit = (v16u8) __msa_fill_b(b_limit_ptr);
    limit = (v16u8) __msa_fill_b(limit_ptr);

    /* mask and hev */
    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit, b_limit, thresh,
                 hev, mask, flat);
    /* flat4 */
    VP9_FLAT4(p3, p2, p0, q0, q2, q3, flat);
    /* filter4 */
    VP9_LPF_FILTER4_4W(p1, p0, q0, q1, mask, hev, p1_out, p0_out, q0_out,
                       q1_out);

    /* if flat is zero for all pixels, then no need to calculate other filter */
    if (__msa_test_bz_v(flat)) {
        ILVR_B2_SH(p0_out, p1_out, q1_out, q0_out, vec0, vec1);
        ILVRL_H2_SH(vec1, vec0, vec2, vec3);
        ILVL_B2_SH(p0_out, p1_out, q1_out, q0_out, vec0, vec1);
        ILVRL_H2_SH(vec1, vec0, vec4, vec5);

        src_org -= 2;
        ST_W8(vec2, vec3, 0, 1, 2, 3, 0, 1, 2, 3, src_org, pitch);
        ST_W8(vec4, vec5, 0, 1, 2, 3, 0, 1, 2, 3, src_org + 8 * pitch, pitch);

        return 1;
    } else {
        ILVR_B8_UH(zero, p3, zero, p2, zero, p1, zero, p0, zero, q0, zero, q1,
                   zero, q2, zero, q3, p3_r, p2_r, p1_r, p0_r, q0_r, q1_r, q2_r,
                   q3_r);
        VP9_FILTER8(p3_r, p2_r, p1_r, p0_r, q0_r, q1_r, q2_r, q3_r, p2_filt8_r,
                    p1_filt8_r, p0_filt8_r, q0_filt8_r, q1_filt8_r, q2_filt8_r);
        ILVL_B4_UH(zero, p3, zero, p2, zero, p1, zero, p0, p3_l, p2_l, p1_l,
                   p0_l);
        ILVL_B4_UH(zero, q0, zero, q1, zero, q2, zero, q3, q0_l, q1_l, q2_l,
                   q3_l);
        VP9_FILTER8(p3_l, p2_l, p1_l, p0_l, q0_l, q1_l, q2_l, q3_l, p2_filt8_l,
                    p1_filt8_l, p0_filt8_l, q0_filt8_l, q1_filt8_l, q2_filt8_l);

        /* convert 16 bit output data into 8 bit */
        PCKEV_B4_SH(p2_filt8_l, p2_filt8_r, p1_filt8_l, p1_filt8_r, p0_filt8_l,
                    p0_filt8_r, q0_filt8_l, q0_filt8_r, p2_filt8_r, p1_filt8_r,
                    p0_filt8_r, q0_filt8_r);
        PCKEV_B2_SH(q1_filt8_l, q1_filt8_r, q2_filt8_l, q2_filt8_r, q1_filt8_r,
                    q2_filt8_r);

        /* store pixel values */
        p2_out = __msa_bmnz_v(p2, (v16u8) p2_filt8_r, flat);
        p1_out = __msa_bmnz_v(p1_out, (v16u8) p1_filt8_r, flat);
        p0_out = __msa_bmnz_v(p0_out, (v16u8) p0_filt8_r, flat);
        q0_out = __msa_bmnz_v(q0_out, (v16u8) q0_filt8_r, flat);
        q1_out = __msa_bmnz_v(q1_out, (v16u8) q1_filt8_r, flat);
        q2_out = __msa_bmnz_v(q2, (v16u8) q2_filt8_r, flat);

        ST_UB4(p2_out, p1_out, p0_out, q0_out, filter48, 16);
        filter48 += (4 * 16);
        ST_UB2(q1_out, q2_out, filter48, 16);
        filter48 += (2 * 16);
        ST_UB(flat, filter48);

        return 0;
    }
}