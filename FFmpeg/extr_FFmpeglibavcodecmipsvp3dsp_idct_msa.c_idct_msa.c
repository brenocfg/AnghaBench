#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int v4i32 ;
typedef  scalar_t__ v16u8 ;
struct TYPE_31__ {int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int CLIP_SW_0_255 (int) ; 
 int /*<<< orphan*/  ILVL_H4_SW (TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_B4_SW (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_H4_SW (TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,int,int,int,int) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST8x1_UB (TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRANSPOSE4x4_SW_SW (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (int,int,int,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 scalar_t__ __msa_and_v (scalar_t__,scalar_t__) ; 
 int __msa_ceqi_w (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_clti_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_ilvl_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_ilvr_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_or_v (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void idct_msa(uint8_t *dst, int stride, int16_t *input, int type)
{
    v8i16 r0, r1, r2, r3, r4, r5, r6, r7, sign;
    v4i32 r0_r, r0_l, r1_r, r1_l, r2_r, r2_l, r3_r, r3_l,
          r4_r, r4_l, r5_r, r5_l, r6_r, r6_l, r7_r, r7_l;
    v4i32 A, B, C, D, Ad, Bd, Cd, Dd, E, F, G, H;
    v4i32 Ed, Gd, Add, Bdd, Fd, Hd;
    v16u8 sign_l;
    v16i8 d0, d1, d2, d3, d4, d5, d6, d7;
    v4i32 c0, c1, c2, c3, c4, c5, c6, c7;
    v4i32 f0, f1, f2, f3, f4, f5, f6, f7;
    v4i32 sign_t;
    v16i8 zero = {0};
    v16i8 mask = {0, 4, 8, 12, 16, 20, 24, 28, 0, 0, 0, 0, 0, 0, 0, 0};
    v4i32 cnst64277w = {64277, 64277, 64277, 64277};
    v4i32 cnst60547w = {60547, 60547, 60547, 60547};
    v4i32 cnst54491w = {54491, 54491, 54491, 54491};
    v4i32 cnst46341w = {46341, 46341, 46341, 46341};
    v4i32 cnst36410w = {36410, 36410, 36410, 36410};
    v4i32 cnst25080w = {25080, 25080, 25080, 25080};
    v4i32 cnst12785w = {12785, 12785, 12785, 12785};
    v4i32 cnst8w = {8, 8, 8, 8};
    v4i32 cnst2048w = {2048, 2048, 2048, 2048};
    v4i32 cnst128w = {128, 128, 128, 128};
    int nstride = stride;

    /* Extended input data */
    LD_SH8(input, 8, r0, r1, r2, r3, r4, r5, r6, r7);
    sign = __msa_clti_s_h(r0, 0);
    r0_r = (v4i32) __msa_ilvr_h(sign, r0);
    r0_l = (v4i32) __msa_ilvl_h(sign, r0);
    sign = __msa_clti_s_h(r1, 0);
    r1_r = (v4i32) __msa_ilvr_h(sign, r1);
    r1_l = (v4i32) __msa_ilvl_h(sign, r1);
    sign = __msa_clti_s_h(r2, 0);
    r2_r = (v4i32) __msa_ilvr_h(sign, r2);
    r2_l = (v4i32) __msa_ilvl_h(sign, r2);
    sign = __msa_clti_s_h(r3, 0);
    r3_r = (v4i32) __msa_ilvr_h(sign, r3);
    r3_l = (v4i32) __msa_ilvl_h(sign, r3);
    sign = __msa_clti_s_h(r4, 0);
    r4_r = (v4i32) __msa_ilvr_h(sign, r4);
    r4_l = (v4i32) __msa_ilvl_h(sign, r4);
    sign = __msa_clti_s_h(r5, 0);
    r5_r = (v4i32) __msa_ilvr_h(sign, r5);
    r5_l = (v4i32) __msa_ilvl_h(sign, r5);
    sign = __msa_clti_s_h(r6, 0);
    r6_r = (v4i32) __msa_ilvr_h(sign, r6);
    r6_l = (v4i32) __msa_ilvl_h(sign, r6);
    sign = __msa_clti_s_h(r7, 0);
    r7_r = (v4i32) __msa_ilvr_h(sign, r7);
    r7_l = (v4i32) __msa_ilvl_h(sign, r7);

    /* Right part */
    A = ((r1_r * cnst64277w) >> 16) + ((r7_r * cnst12785w) >> 16);
    B = ((r1_r * cnst12785w) >> 16) - ((r7_r * cnst64277w) >> 16);
    C = ((r3_r * cnst54491w) >> 16) + ((r5_r * cnst36410w) >> 16);
    D = ((r5_r * cnst54491w) >> 16) - ((r3_r * cnst36410w) >> 16);
    Ad = ((A - C) * cnst46341w) >> 16;
    Bd = ((B - D) * cnst46341w) >> 16;
    Cd = A + C;
    Dd = B + D;
    E = ((r0_r + r4_r) * cnst46341w) >> 16;
    F = ((r0_r - r4_r) * cnst46341w) >> 16;
    G = ((r2_r * cnst60547w) >> 16) + ((r6_r * cnst25080w) >> 16);
    H = ((r2_r * cnst25080w) >> 16) - ((r6_r * cnst60547w) >> 16);
    Ed = E - G;
    Gd = E + G;
    Add = F + Ad;
    Bdd = Bd - H;
    Fd = F - Ad;
    Hd = Bd + H;
    r0_r = Gd + Cd;
    r7_r = Gd - Cd;
    r1_r = Add + Hd;
    r2_r = Add - Hd;
    r3_r = Ed + Dd;
    r4_r = Ed - Dd;
    r5_r = Fd + Bdd;
    r6_r = Fd - Bdd;

    /* Left part */
    A = ((r1_l * cnst64277w) >> 16) + ((r7_l * cnst12785w) >> 16);
    B = ((r1_l * cnst12785w) >> 16) - ((r7_l * cnst64277w) >> 16);
    C = ((r3_l * cnst54491w) >> 16) + ((r5_l * cnst36410w) >> 16);
    D = ((r5_l * cnst54491w) >> 16) - ((r3_l * cnst36410w) >> 16);
    Ad = ((A - C) * cnst46341w) >> 16;
    Bd = ((B - D) * cnst46341w) >> 16;
    Cd = A + C;
    Dd = B + D;
    E = ((r0_l + r4_l) * cnst46341w) >> 16;
    F = ((r0_l - r4_l) * cnst46341w) >> 16;
    G = ((r2_l * cnst60547w) >> 16) + ((r6_l * cnst25080w) >> 16);
    H = ((r2_l * cnst25080w) >> 16) - ((r6_l * cnst60547w) >> 16);
    Ed = E - G;
    Gd = E + G;
    Add = F + Ad;
    Bdd = Bd - H;
    Fd = F - Ad;
    Hd = Bd + H;
    r0_l = Gd + Cd;
    r7_l = Gd - Cd;
    r1_l = Add + Hd;
    r2_l = Add - Hd;
    r3_l = Ed + Dd;
    r4_l = Ed - Dd;
    r5_l = Fd + Bdd;
    r6_l = Fd - Bdd;

    /* Row 0 to 3 */
    TRANSPOSE4x4_SW_SW(r0_r, r1_r, r2_r, r3_r,
                       r0_r, r1_r, r2_r, r3_r);
    TRANSPOSE4x4_SW_SW(r0_l, r1_l, r2_l, r3_l,
                       r0_l, r1_l, r2_l, r3_l);
    A = ((r1_r * cnst64277w) >> 16) + ((r3_l * cnst12785w) >> 16);
    B = ((r1_r * cnst12785w) >> 16) - ((r3_l * cnst64277w) >> 16);
    C = ((r3_r * cnst54491w) >> 16) + ((r1_l * cnst36410w) >> 16);
    D = ((r1_l * cnst54491w) >> 16) - ((r3_r * cnst36410w) >> 16);
    Ad = ((A - C) * cnst46341w) >> 16;
    Bd = ((B - D) * cnst46341w) >> 16;
    Cd = A + C;
    Dd = B + D;
    E = ((r0_r + r0_l) * cnst46341w) >> 16;
    E += cnst8w;
    F = ((r0_r - r0_l) * cnst46341w) >> 16;
    F += cnst8w;
    if (type == 1) { // HACK
        E += cnst2048w;
        F += cnst2048w;
    }
    G = ((r2_r * cnst60547w) >> 16) + ((r2_l * cnst25080w) >> 16);
    H = ((r2_r * cnst25080w) >> 16) - ((r2_l * cnst60547w) >> 16);
    Ed = E - G;
    Gd = E + G;
    Add = F + Ad;
    Bdd = Bd - H;
    Fd = F - Ad;
    Hd = Bd + H;
    A = (Gd + Cd) >> 4;
    B = (Gd - Cd) >> 4;
    C = (Add + Hd) >> 4;
    D = (Add - Hd) >> 4;
    E = (Ed + Dd) >> 4;
    F = (Ed - Dd) >> 4;
    G = (Fd + Bdd) >> 4;
    H = (Fd - Bdd) >> 4;
    if (type != 1) {
        LD_SB8(dst, stride, d0, d1, d2, d3, d4, d5, d6, d7);
        ILVR_B4_SW(zero, d0, zero, d1, zero, d2, zero, d3,
                   f0, f1, f2, f3);
        ILVR_B4_SW(zero, d4, zero, d5, zero, d6, zero, d7,
                   f4, f5, f6, f7);
        ILVR_H4_SW(zero, f0, zero, f1, zero, f2, zero, f3,
                   c0, c1, c2, c3);
        ILVR_H4_SW(zero, f4, zero, f5, zero, f6, zero, f7,
                   c4, c5, c6, c7);
        A += c0;
        B += c7;
        C += c1;
        D += c2;
        E += c3;
        F += c4;
        G += c5;
        H += c6;
    }
    A = CLIP_SW_0_255(A);
    B = CLIP_SW_0_255(B);
    C = CLIP_SW_0_255(C);
    D = CLIP_SW_0_255(D);
    E = CLIP_SW_0_255(E);
    F = CLIP_SW_0_255(F);
    G = CLIP_SW_0_255(G);
    H = CLIP_SW_0_255(H);
    sign_l = __msa_or_v((v16u8)r1_r, (v16u8)r2_r);
    sign_l = __msa_or_v(sign_l, (v16u8)r3_r);
    sign_l = __msa_or_v(sign_l, (v16u8)r0_l);
    sign_l = __msa_or_v(sign_l, (v16u8)r1_l);
    sign_l = __msa_or_v(sign_l, (v16u8)r2_l);
    sign_l = __msa_or_v(sign_l, (v16u8)r3_l);
    sign_t = __msa_ceqi_w((v4i32)sign_l, 0);
    Add = ((r0_r * cnst46341w) + (8 << 16)) >> 20;
    if (type == 1) {
        Bdd = Add + cnst128w;
        Bdd = CLIP_SW_0_255(Bdd);
        Ad = Bdd;
        Bd = Bdd;
        Cd = Bdd;
        Dd = Bdd;
        Ed = Bdd;
        Fd = Bdd;
        Gd = Bdd;
        Hd = Bdd;
    } else {
        Ad = Add + c0;
        Bd = Add + c1;
        Cd = Add + c2;
        Dd = Add + c3;
        Ed = Add + c4;
        Fd = Add + c5;
        Gd = Add + c6;
        Hd = Add + c7;
        Ad = CLIP_SW_0_255(Ad);
        Bd = CLIP_SW_0_255(Bd);
        Cd = CLIP_SW_0_255(Cd);
        Dd = CLIP_SW_0_255(Dd);
        Ed = CLIP_SW_0_255(Ed);
        Fd = CLIP_SW_0_255(Fd);
        Gd = CLIP_SW_0_255(Gd);
        Hd = CLIP_SW_0_255(Hd);
    }
    Ad = (v4i32)__msa_and_v((v16u8)Ad, (v16u8)sign_t);
    Bd = (v4i32)__msa_and_v((v16u8)Bd, (v16u8)sign_t);
    Cd = (v4i32)__msa_and_v((v16u8)Cd, (v16u8)sign_t);
    Dd = (v4i32)__msa_and_v((v16u8)Dd, (v16u8)sign_t);
    Ed = (v4i32)__msa_and_v((v16u8)Ed, (v16u8)sign_t);
    Fd = (v4i32)__msa_and_v((v16u8)Fd, (v16u8)sign_t);
    Gd = (v4i32)__msa_and_v((v16u8)Gd, (v16u8)sign_t);
    Hd = (v4i32)__msa_and_v((v16u8)Hd, (v16u8)sign_t);
    sign_t = __msa_ceqi_w(sign_t, 0);
    A = (v4i32)__msa_and_v((v16u8)A, (v16u8)sign_t);
    B = (v4i32)__msa_and_v((v16u8)B, (v16u8)sign_t);
    C = (v4i32)__msa_and_v((v16u8)C, (v16u8)sign_t);
    D = (v4i32)__msa_and_v((v16u8)D, (v16u8)sign_t);
    E = (v4i32)__msa_and_v((v16u8)E, (v16u8)sign_t);
    F = (v4i32)__msa_and_v((v16u8)F, (v16u8)sign_t);
    G = (v4i32)__msa_and_v((v16u8)G, (v16u8)sign_t);
    H = (v4i32)__msa_and_v((v16u8)H, (v16u8)sign_t);
    r0_r = Ad + A;
    r1_r = Bd + C;
    r2_r = Cd + D;
    r3_r = Dd + E;
    r0_l = Ed + F;
    r1_l = Fd + G;
    r2_l = Gd + H;
    r3_l = Hd + B;

    /* Row 4 to 7 */
    TRANSPOSE4x4_SW_SW(r4_r, r5_r, r6_r, r7_r,
                       r4_r, r5_r, r6_r, r7_r);
    TRANSPOSE4x4_SW_SW(r4_l, r5_l, r6_l, r7_l,
                       r4_l, r5_l, r6_l, r7_l);
    A = ((r5_r * cnst64277w) >> 16) + ((r7_l * cnst12785w) >> 16);
    B = ((r5_r * cnst12785w) >> 16) - ((r7_l * cnst64277w) >> 16);
    C = ((r7_r * cnst54491w) >> 16) + ((r5_l * cnst36410w) >> 16);
    D = ((r5_l * cnst54491w) >> 16) - ((r7_r * cnst36410w) >> 16);
    Ad = ((A - C) * cnst46341w) >> 16;
    Bd = ((B - D) * cnst46341w) >> 16;
    Cd = A + C;
    Dd = B + D;
    E = ((r4_r + r4_l) * cnst46341w) >> 16;
    E += cnst8w;
    F = ((r4_r - r4_l) * cnst46341w) >> 16;
    F += cnst8w;
    if (type == 1) { // HACK
        E += cnst2048w;
        F += cnst2048w;
    }
    G = ((r6_r * cnst60547w) >> 16) + ((r6_l * cnst25080w) >> 16);
    H = ((r6_r * cnst25080w) >> 16) - ((r6_l * cnst60547w) >> 16);
    Ed = E - G;
    Gd = E + G;
    Add = F + Ad;
    Bdd = Bd - H;
    Fd = F - Ad;
    Hd = Bd + H;
    A = (Gd + Cd) >> 4;
    B = (Gd - Cd) >> 4;
    C = (Add + Hd) >> 4;
    D = (Add - Hd) >> 4;
    E = (Ed + Dd) >> 4;
    F = (Ed - Dd) >> 4;
    G = (Fd + Bdd) >> 4;
    H = (Fd - Bdd) >> 4;
    if (type != 1) {
        ILVL_H4_SW(zero, f0, zero, f1, zero, f2, zero, f3,
                   c0, c1, c2, c3);
        ILVL_H4_SW(zero, f4, zero, f5, zero, f6, zero, f7,
                   c4, c5, c6, c7);
        A += c0;
        B += c7;
        C += c1;
        D += c2;
        E += c3;
        F += c4;
        G += c5;
        H += c6;
    }
    A = CLIP_SW_0_255(A);
    B = CLIP_SW_0_255(B);
    C = CLIP_SW_0_255(C);
    D = CLIP_SW_0_255(D);
    E = CLIP_SW_0_255(E);
    F = CLIP_SW_0_255(F);
    G = CLIP_SW_0_255(G);
    H = CLIP_SW_0_255(H);
    sign_l = __msa_or_v((v16u8)r5_r, (v16u8)r6_r);
    sign_l = __msa_or_v(sign_l, (v16u8)r7_r);
    sign_l = __msa_or_v(sign_l, (v16u8)r4_l);
    sign_l = __msa_or_v(sign_l, (v16u8)r5_l);
    sign_l = __msa_or_v(sign_l, (v16u8)r6_l);
    sign_l = __msa_or_v(sign_l, (v16u8)r7_l);
    sign_t = __msa_ceqi_w((v4i32)sign_l, 0);
    Add = ((r4_r * cnst46341w) + (8 << 16)) >> 20;
    if (type == 1) {
        Bdd = Add + cnst128w;
        Bdd = CLIP_SW_0_255(Bdd);
        Ad = Bdd;
        Bd = Bdd;
        Cd = Bdd;
        Dd = Bdd;
        Ed = Bdd;
        Fd = Bdd;
        Gd = Bdd;
        Hd = Bdd;
    } else {
        Ad = Add + c0;
        Bd = Add + c1;
        Cd = Add + c2;
        Dd = Add + c3;
        Ed = Add + c4;
        Fd = Add + c5;
        Gd = Add + c6;
        Hd = Add + c7;
        Ad = CLIP_SW_0_255(Ad);
        Bd = CLIP_SW_0_255(Bd);
        Cd = CLIP_SW_0_255(Cd);
        Dd = CLIP_SW_0_255(Dd);
        Ed = CLIP_SW_0_255(Ed);
        Fd = CLIP_SW_0_255(Fd);
        Gd = CLIP_SW_0_255(Gd);
        Hd = CLIP_SW_0_255(Hd);
    }
    Ad = (v4i32)__msa_and_v((v16u8)Ad, (v16u8)sign_t);
    Bd = (v4i32)__msa_and_v((v16u8)Bd, (v16u8)sign_t);
    Cd = (v4i32)__msa_and_v((v16u8)Cd, (v16u8)sign_t);
    Dd = (v4i32)__msa_and_v((v16u8)Dd, (v16u8)sign_t);
    Ed = (v4i32)__msa_and_v((v16u8)Ed, (v16u8)sign_t);
    Fd = (v4i32)__msa_and_v((v16u8)Fd, (v16u8)sign_t);
    Gd = (v4i32)__msa_and_v((v16u8)Gd, (v16u8)sign_t);
    Hd = (v4i32)__msa_and_v((v16u8)Hd, (v16u8)sign_t);
    sign_t = __msa_ceqi_w(sign_t, 0);
    A = (v4i32)__msa_and_v((v16u8)A, (v16u8)sign_t);
    B = (v4i32)__msa_and_v((v16u8)B, (v16u8)sign_t);
    C = (v4i32)__msa_and_v((v16u8)C, (v16u8)sign_t);
    D = (v4i32)__msa_and_v((v16u8)D, (v16u8)sign_t);
    E = (v4i32)__msa_and_v((v16u8)E, (v16u8)sign_t);
    F = (v4i32)__msa_and_v((v16u8)F, (v16u8)sign_t);
    G = (v4i32)__msa_and_v((v16u8)G, (v16u8)sign_t);
    H = (v4i32)__msa_and_v((v16u8)H, (v16u8)sign_t);
    r4_r = Ad + A;
    r5_r = Bd + C;
    r6_r = Cd + D;
    r7_r = Dd + E;
    r4_l = Ed + F;
    r5_l = Fd + G;
    r6_l = Gd + H;
    r7_l = Hd + B;
    VSHF_B2_SB(r0_r, r4_r, r1_r, r5_r, mask, mask, d0, d1);
    VSHF_B2_SB(r2_r, r6_r, r3_r, r7_r, mask, mask, d2, d3);
    VSHF_B2_SB(r0_l, r4_l, r1_l, r5_l, mask, mask, d4, d5);
    VSHF_B2_SB(r2_l, r6_l, r3_l, r7_l, mask, mask, d6, d7);

    /* Final sequence of operations over-write original dst */
    ST8x1_UB(d0, dst);
    ST8x1_UB(d1, dst + nstride);
    nstride += stride;
    ST8x1_UB(d2, dst + nstride);
    nstride += stride;
    ST8x1_UB(d3, dst + nstride);
    nstride += stride;
    ST8x1_UB(d4, dst + nstride);
    nstride += stride;
    ST8x1_UB(d5, dst + nstride);
    nstride += stride;
    ST8x1_UB(d6, dst + nstride);
    nstride += stride;
    ST8x1_UB(d7, dst + nstride);
}