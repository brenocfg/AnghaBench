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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  HADD_UB2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_UB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ST_UB8 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_hadd_u_d (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_hadd_u_w (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_pckev_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_splati_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_srari_w (int /*<<< orphan*/ ,int) ; 

void ff_dc_16x16_msa(uint8_t *dst, ptrdiff_t dst_stride,
                     const uint8_t *src_left, const uint8_t *src_top)
{
    v16u8 top, left, out;
    v8u16 sum_h, sum_top, sum_left;
    v4u32 sum_w;
    v2u64 sum_d;

    top = LD_UB(src_top);
    left = LD_UB(src_left);
    HADD_UB2_UH(top, left, sum_top, sum_left);
    sum_h = sum_top + sum_left;
    sum_w = __msa_hadd_u_w(sum_h, sum_h);
    sum_d = __msa_hadd_u_d(sum_w, sum_w);
    sum_w = (v4u32) __msa_pckev_w((v4i32) sum_d, (v4i32) sum_d);
    sum_d = __msa_hadd_u_d(sum_w, sum_w);
    sum_w = (v4u32) __msa_srari_w((v4i32) sum_d, 5);
    out = (v16u8) __msa_splati_b((v16i8) sum_w, 0);

    ST_UB8(out, out, out, out, out, out, out, out, dst, dst_stride);
    dst += (8 * dst_stride);
    ST_UB8(out, out, out, out, out, out, out, out, dst, dst_stride);
}