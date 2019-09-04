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
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  avc_loopfilter_luma_inter_edge_ver_msa (int*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

void ff_h264_h_lpf_luma_inter_msa(uint8_t *data, int img_width,
                                  int alpha, int beta, int8_t *tc)
{
    uint8_t bs0 = 1;
    uint8_t bs1 = 1;
    uint8_t bs2 = 1;
    uint8_t bs3 = 1;

    if (tc[0] < 0)
        bs0 = 0;
    if (tc[1] < 0)
        bs1 = 0;
    if (tc[2] < 0)
        bs2 = 0;
    if (tc[3] < 0)
        bs3 = 0;

    avc_loopfilter_luma_inter_edge_ver_msa(data, bs0, bs1, bs2, bs3,
                                           tc[0], tc[1], tc[2], tc[3],
                                           alpha, beta, img_width);
}