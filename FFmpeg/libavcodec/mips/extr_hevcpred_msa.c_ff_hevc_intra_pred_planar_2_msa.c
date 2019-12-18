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
 int /*<<< orphan*/  hevc_intra_pred_plane_16x16_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ff_hevc_intra_pred_planar_2_msa(uint8_t *dst,
                                     const uint8_t *src_top,
                                     const uint8_t *src_left,
                                     ptrdiff_t stride)
{
    hevc_intra_pred_plane_16x16_msa(src_top, src_left, dst, stride);
}