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
typedef  scalar_t__ v8u16 ;
typedef  scalar_t__ v4u32 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  scalar_t__ v2u64 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  HADD_UB2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB2 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_UB2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_hadd_u_d (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_hadd_u_w (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_pckev_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_splati_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_srari_w (int /*<<< orphan*/ ,int) ; 

void ff_dc_32x32_msa(uint8_t *dst, ptrdiff_t dst_stride,
                     const uint8_t *src_left, const uint8_t *src_top)
{
    uint32_t row;
    v16u8 top0, top1, left0, left1, out;
    v8u16 sum_h, sum_top0, sum_top1, sum_left0, sum_left1;
    v4u32 sum_w;
    v2u64 sum_d;

    LD_UB2(src_top, 16, top0, top1);
    LD_UB2(src_left, 16, left0, left1);
    HADD_UB2_UH(top0, top1, sum_top0, sum_top1);
    HADD_UB2_UH(left0, left1, sum_left0, sum_left1);
    sum_h = sum_top0 + sum_top1;
    sum_h += sum_left0 + sum_left1;
    sum_w = __msa_hadd_u_w(sum_h, sum_h);
    sum_d = __msa_hadd_u_d(sum_w, sum_w);
    sum_w = (v4u32) __msa_pckev_w((v4i32) sum_d, (v4i32) sum_d);
    sum_d = __msa_hadd_u_d(sum_w, sum_w);
    sum_w = (v4u32) __msa_srari_w((v4i32) sum_d, 6);
    out = (v16u8) __msa_splati_b((v16i8) sum_w, 0);

    for (row = 16; row--;)
    {
        ST_UB2(out, out, dst, 16);
        dst += dst_stride;
        ST_UB2(out, out, dst, 16);
        dst += dst_stride;
    }
}