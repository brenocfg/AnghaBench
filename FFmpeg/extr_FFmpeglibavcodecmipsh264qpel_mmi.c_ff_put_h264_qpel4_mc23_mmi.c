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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_put_pixels4_l2_8_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  put_h264_qpel4_h_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_h264_qpel4_hv_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

void ff_put_h264_qpel4_mc23_mmi(uint8_t *dst, const uint8_t *src,
        ptrdiff_t stride)
{
    uint8_t halfH[16];
    uint8_t halfHV[16];
    put_h264_qpel4_h_lowpass_mmi(halfH, src + stride, 4, stride);
    put_h264_qpel4_hv_lowpass_mmi(halfHV, src, 4, stride);
    ff_put_pixels4_l2_8_mmi(dst, halfH, halfHV, stride, 4, 4, 4);
}