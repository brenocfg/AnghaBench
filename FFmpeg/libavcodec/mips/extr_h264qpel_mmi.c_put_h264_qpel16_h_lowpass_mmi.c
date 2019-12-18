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

/* Variables and functions */
 int /*<<< orphan*/  put_h264_qpel8_h_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void put_h264_qpel16_h_lowpass_mmi(uint8_t *dst, const uint8_t *src,
        int dstStride, int srcStride)
{
    put_h264_qpel8_h_lowpass_mmi(dst, src, dstStride, srcStride);
    put_h264_qpel8_h_lowpass_mmi(dst+8, src+8, dstStride, srcStride);
    src += 8*srcStride;
    dst += 8*dstStride;
    put_h264_qpel8_h_lowpass_mmi(dst, src, dstStride, srcStride);
    put_h264_qpel8_h_lowpass_mmi(dst+8, src+8, dstStride, srcStride);
}