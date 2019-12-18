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
 int /*<<< orphan*/  avc_luma_hv_qrt_8x8_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

void ff_put_h264_qpel8_mc31_msa(uint8_t *dst, const uint8_t *src,
                                ptrdiff_t stride)
{
    avc_luma_hv_qrt_8x8_msa(src - 2, src - (stride * 2) + 1, dst, stride);
}