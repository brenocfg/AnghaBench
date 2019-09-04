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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_SH (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_SH4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE8x8_SH_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vp9_idct_butterfly_transpose_store(int16_t *tmp_buf,
                                               int16_t *tmp_eve_buf,
                                               int16_t *tmp_odd_buf,
                                               int16_t *dst)
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

    ST_SH((loc0 - vec3), (tmp_buf + 31 * 8));
    ST_SH((loc1 - vec2), (tmp_buf + 23 * 8));
    ST_SH((loc2 - vec1), (tmp_buf + 27 * 8));
    ST_SH((loc3 - vec0), (tmp_buf + 19 * 8));

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

    ST_SH((loc0 - vec3), (tmp_buf + 29 * 8));
    ST_SH((loc1 - vec2), (tmp_buf + 21 * 8));
    ST_SH((loc2 - vec1), (tmp_buf + 25 * 8));
    ST_SH((loc3 - vec0), (tmp_buf + 17 * 8));

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

    ST_SH((loc0 - vec3), (tmp_buf + 30 * 8));
    ST_SH((loc1 - vec2), (tmp_buf + 22 * 8));
    ST_SH((loc2 - vec1), (tmp_buf + 26 * 8));
    ST_SH((loc3 - vec0), (tmp_buf + 18 * 8));

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

    ST_SH((loc0 - vec3), (tmp_buf + 28 * 8));
    ST_SH((loc1 - vec2), (tmp_buf + 20 * 8));
    ST_SH((loc2 - vec1), (tmp_buf + 24 * 8));
    ST_SH((loc3 - vec0), (tmp_buf + 16 * 8));

    /* Transpose : 16 vectors */
    /* 1st & 2nd 8x8 */
    TRANSPOSE8x8_SH_SH(m0, n0, m1, n1, m2, n2, m3, n3,
                       m0, n0, m1, n1, m2, n2, m3, n3);
    ST_SH4(m0, n0, m1, n1, (dst + 0), 32);
    ST_SH4(m2, n2, m3, n3, (dst + 4 * 32), 32);

    TRANSPOSE8x8_SH_SH(m4, n4, m5, n5, m6, n6, m7, n7,
                       m4, n4, m5, n5, m6, n6, m7, n7);
    ST_SH4(m4, n4, m5, n5, (dst + 8), 32);
    ST_SH4(m6, n6, m7, n7, (dst + 8 + 4 * 32), 32);

    /* 3rd & 4th 8x8 */
    LD_SH8((tmp_buf + 8 * 16), 8, m0, n0, m1, n1, m2, n2, m3, n3);
    LD_SH8((tmp_buf + 12 * 16), 8, m4, n4, m5, n5, m6, n6, m7, n7);
    TRANSPOSE8x8_SH_SH(m0, n0, m1, n1, m2, n2, m3, n3,
                       m0, n0, m1, n1, m2, n2, m3, n3);
    ST_SH4(m0, n0, m1, n1, (dst + 16), 32);
    ST_SH4(m2, n2, m3, n3, (dst + 16 + 4 * 32), 32);

    TRANSPOSE8x8_SH_SH(m4, n4, m5, n5, m6, n6, m7, n7,
                       m4, n4, m5, n5, m6, n6, m7, n7);
    ST_SH4(m4, n4, m5, n5, (dst + 24), 32);
    ST_SH4(m6, n6, m7, n7, (dst + 24 + 4 * 32), 32);
}