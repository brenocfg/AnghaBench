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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  copy_block16_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  ff_avg_pixels16_l2_8_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  put_h264_qpel16_h_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  put_h264_qpel16_v_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int,int) ; 

void ff_avg_h264_qpel16_mc13_mmi(uint8_t *dst, const uint8_t *src,
        ptrdiff_t stride)
{
    uint8_t full[336];
    uint8_t * const full_mid= full + 32;
    uint8_t halfH[256];
    uint8_t halfV[256];
    put_h264_qpel16_h_lowpass_mmi(halfH, src + stride, 16, stride);
    copy_block16_mmi(full, src - stride*2, 16,  stride, 21);
    put_h264_qpel16_v_lowpass_mmi(halfV, full_mid, 16, 16);
    ff_avg_pixels16_l2_8_mmi(dst, halfH, halfV, stride, 16, 16, 16);
}