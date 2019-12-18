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
typedef  scalar_t__ v16u8 ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  size_t ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST_UB8 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int*,size_t) ; 
 scalar_t__ __msa_fill_b (int) ; 

void ff_h264_intra_pred_dc_left_16x16_msa(uint8_t *src, ptrdiff_t stride)
{
    uint8_t *src_left = src - 1;
    uint8_t *dst = src;
    uint32_t addition;
    v16u8 out;

    addition  = src_left[ 0 * stride];
    addition += src_left[ 1 * stride];
    addition += src_left[ 2 * stride];
    addition += src_left[ 3 * stride];
    addition += src_left[ 4 * stride];
    addition += src_left[ 5 * stride];
    addition += src_left[ 6 * stride];
    addition += src_left[ 7 * stride];
    addition += src_left[ 8 * stride];
    addition += src_left[ 9 * stride];
    addition += src_left[10 * stride];
    addition += src_left[11 * stride];
    addition += src_left[12 * stride];
    addition += src_left[13 * stride];
    addition += src_left[14 * stride];
    addition += src_left[15 * stride];

    addition = (addition + 8) >> 4;
    out = (v16u8) __msa_fill_b(addition);

    ST_UB8(out, out, out, out, out, out, out, out, dst, stride);
    dst += (8 * stride);
    ST_UB8(out, out, out, out, out, out, out, out, dst, stride);
}