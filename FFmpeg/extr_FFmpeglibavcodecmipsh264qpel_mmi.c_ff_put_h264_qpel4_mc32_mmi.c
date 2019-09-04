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
 int /*<<< orphan*/  copy_block4_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  ff_put_pixels4_l2_8_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  put_h264_qpel4_hv_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  put_h264_qpel4_v_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int,int) ; 

void ff_put_h264_qpel4_mc32_mmi(uint8_t *dst, const uint8_t *src,
        ptrdiff_t stride)
{
    uint8_t full[36];
    uint8_t * const full_mid= full + 8;
    uint8_t halfV[16];
    uint8_t halfHV[16];
    copy_block4_mmi(full, src - stride*2 + 1, 4,  stride, 9);
    put_h264_qpel4_v_lowpass_mmi(halfV, full_mid, 4, 4);
    put_h264_qpel4_hv_lowpass_mmi(halfHV, src, 4, stride);
    ff_put_pixels4_l2_8_mmi(dst, halfV, halfHV, stride, 4, 4, 4);
}