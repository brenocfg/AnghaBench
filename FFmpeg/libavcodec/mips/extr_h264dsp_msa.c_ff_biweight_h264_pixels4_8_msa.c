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
 int /*<<< orphan*/  avc_biwgt_4x2_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  avc_biwgt_4x4_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  avc_biwgt_4x8_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

void ff_biweight_h264_pixels4_8_msa(uint8_t *dst, uint8_t *src,
                                    ptrdiff_t stride, int height,
                                    int log2_denom, int weight_dst,
                                    int weight_src, int offset)
{
    if (2 == height) {
        avc_biwgt_4x2_msa(src, dst, stride, log2_denom, weight_src, weight_dst,
                          offset);
    } else if (4 == height) {
        avc_biwgt_4x4_msa(src, dst, stride, log2_denom, weight_src, weight_dst,
                          offset);
    } else {
        avc_biwgt_4x8_msa(src, dst, stride, log2_denom, weight_src, weight_dst,
                          offset);
    }
}