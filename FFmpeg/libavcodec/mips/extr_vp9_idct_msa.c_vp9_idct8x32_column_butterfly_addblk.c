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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SUB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP9_ADDBLK_ST8x4_UB (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp9_idct8x32_column_butterfly_addblk(int16_t *tmp_eve_buf,
                                                 int16_t *tmp_odd_buf,
                                                 uint8_t *dst,
                                                 int32_t dst_stride)
{
    v8i16 vec0, vec1, vec2, vec3, loc0, loc1, loc2, loc3;
    v8i16 m0, m1, m2, m3, m4, m5, m6, m7, n0, n1, n2, n3, n4, n5, n6, n7;

    /* FINAL BUTTERFLY : Dependency on Even & Odd */
    vec0 = LD_SH(tmp_odd_buf);
    vec1 = LD_SH(tmp_odd_buf + 9 * 8);
    vec2 = LD_SH(tmp_odd_buf + 14 * 8);
    vec3 = LD_SH(tmp_odd_buf + 6 * 8);
    loc0 = LD_SH(tmp_eve_buf);
    loc1 = LD_SH(tmp_eve_buf + 8 * 8);
    loc2 = LD_SH(tmp_eve_buf + 4 * 8);
    loc3 = LD_SH(tmp_eve_buf + 12 * 8);

    ADD4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, m0, m4, m2, m6);
    SRARI_H4_SH(m0, m2, m4, m6, 6);
    VP9_ADDBLK_ST8x4_UB(dst, (4 * dst_stride), m0, m2, m4, m6);

    SUB4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, m6, m2, m4, m0);
    SRARI_H4_SH(m0, m2, m4, m6, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 19 * dst_stride), (4 * dst_stride),
                        m0, m2, m4, m6);

    /* Load 8 & Store 8 */
    vec0 = LD_SH(tmp_odd_buf + 4 * 8);
    vec1 = LD_SH(tmp_odd_buf + 13 * 8);
    vec2 = LD_SH(tmp_odd_buf + 10 * 8);
    vec3 = LD_SH(tmp_odd_buf + 3 * 8);
    loc0 = LD_SH(tmp_eve_buf + 2 * 8);
    loc1 = LD_SH(tmp_eve_buf + 10 * 8);
    loc2 = LD_SH(tmp_eve_buf + 6 * 8);
    loc3 = LD_SH(tmp_eve_buf + 14 * 8);

    ADD4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, m1, m5, m3, m7);
    SRARI_H4_SH(m1, m3, m5, m7, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 2 * dst_stride), (4 * dst_stride),
                        m1, m3, m5, m7);

    SUB4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, m7, m3, m5, m1);
    SRARI_H4_SH(m1, m3, m5, m7, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 17 * dst_stride), (4 * dst_stride),
                        m1, m3, m5, m7);

    /* Load 8 & Store 8 */
    vec0 = LD_SH(tmp_odd_buf + 2 * 8);
    vec1 = LD_SH(tmp_odd_buf + 11 * 8);
    vec2 = LD_SH(tmp_odd_buf + 12 * 8);
    vec3 = LD_SH(tmp_odd_buf + 7 * 8);
    loc0 = LD_SH(tmp_eve_buf + 1 * 8);
    loc1 = LD_SH(tmp_eve_buf + 9 * 8);
    loc2 = LD_SH(tmp_eve_buf + 5 * 8);
    loc3 = LD_SH(tmp_eve_buf + 13 * 8);

    ADD4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, n0, n4, n2, n6);
    SRARI_H4_SH(n0, n2, n4, n6, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 1 * dst_stride), (4 * dst_stride),
                        n0, n2, n4, n6);

    SUB4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, n6, n2, n4, n0);
    SRARI_H4_SH(n0, n2, n4, n6, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 18 * dst_stride), (4 * dst_stride),
                        n0, n2, n4, n6);

    /* Load 8 & Store 8 */
    vec0 = LD_SH(tmp_odd_buf + 5 * 8);
    vec1 = LD_SH(tmp_odd_buf + 15 * 8);
    vec2 = LD_SH(tmp_odd_buf + 8 * 8);
    vec3 = LD_SH(tmp_odd_buf + 1 * 8);
    loc0 = LD_SH(tmp_eve_buf + 3 * 8);
    loc1 = LD_SH(tmp_eve_buf + 11 * 8);
    loc2 = LD_SH(tmp_eve_buf + 7 * 8);
    loc3 = LD_SH(tmp_eve_buf + 15 * 8);

    ADD4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, n1, n5, n3, n7);
    SRARI_H4_SH(n1, n3, n5, n7, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 3 * dst_stride), (4 * dst_stride),
                        n1, n3, n5, n7);

    SUB4(loc0, vec3, loc1, vec2, loc2, vec1, loc3, vec0, n7, n3, n5, n1);
    SRARI_H4_SH(n1, n3, n5, n7, 6);
    VP9_ADDBLK_ST8x4_UB((dst + 16 * dst_stride), (4 * dst_stride),
                        n1, n3, n5, n7);
}