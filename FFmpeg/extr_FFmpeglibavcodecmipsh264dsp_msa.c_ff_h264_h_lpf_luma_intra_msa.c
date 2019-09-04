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
 int /*<<< orphan*/  avc_loopfilter_luma_intra_edge_ver_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void ff_h264_h_lpf_luma_intra_msa(uint8_t *data, int img_width,
                                  int alpha, int beta)
{
    avc_loopfilter_luma_intra_edge_ver_msa(data, (uint8_t) alpha,
                                           (uint8_t) beta,
                                           (unsigned int) img_width);
}