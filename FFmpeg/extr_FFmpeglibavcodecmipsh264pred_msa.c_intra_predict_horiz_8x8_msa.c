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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SD4 (int,int,int,int,int*,size_t) ; 

__attribute__((used)) static void intra_predict_horiz_8x8_msa(uint8_t *src, int32_t src_stride,
                                        uint8_t *dst, int32_t dst_stride)
{
    uint64_t out0, out1, out2, out3, out4, out5, out6, out7;

    out0 = src[0 * src_stride] * 0x0101010101010101;
    out1 = src[1 * src_stride] * 0x0101010101010101;
    out2 = src[2 * src_stride] * 0x0101010101010101;
    out3 = src[3 * src_stride] * 0x0101010101010101;
    out4 = src[4 * src_stride] * 0x0101010101010101;
    out5 = src[5 * src_stride] * 0x0101010101010101;
    out6 = src[6 * src_stride] * 0x0101010101010101;
    out7 = src[7 * src_stride] * 0x0101010101010101;

    SD4(out0, out1, out2, out3, dst, dst_stride);
    dst += (4 * dst_stride);
    SD4(out4, out5, out6, out7, dst, dst_stride);
}