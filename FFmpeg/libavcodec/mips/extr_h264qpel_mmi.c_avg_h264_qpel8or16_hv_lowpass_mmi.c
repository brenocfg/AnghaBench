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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  avg_h264_qpel8or16_hv2_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_h264_qpel8or16_hv1_lowpass_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void avg_h264_qpel8or16_hv_lowpass_mmi(uint8_t *dst, int16_t *tmp,
        const uint8_t *src, ptrdiff_t dstStride, ptrdiff_t tmpStride,
        ptrdiff_t srcStride, int size)
{
    put_h264_qpel8or16_hv1_lowpass_mmi(tmp, src, tmpStride, srcStride, size);
    avg_h264_qpel8or16_hv2_lowpass_mmi(dst, tmp, dstStride, tmpStride, size);
}