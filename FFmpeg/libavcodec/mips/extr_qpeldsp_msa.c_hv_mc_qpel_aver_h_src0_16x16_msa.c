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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hv_mc_qpel_aver_horiz_src0_16x16_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vert_mc_qpel_16x16_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_mc_qpel_aver_h_src0_16x16_msa(const uint8_t *src,
                                             int32_t src_stride,
                                             uint8_t *dst,
                                             int32_t dst_stride)
{
    uint8_t buff[272];

    hv_mc_qpel_aver_horiz_src0_16x16_msa(src, src_stride, buff, 16, 16);
    vert_mc_qpel_16x16_msa(buff, 16, dst, dst_stride);
}