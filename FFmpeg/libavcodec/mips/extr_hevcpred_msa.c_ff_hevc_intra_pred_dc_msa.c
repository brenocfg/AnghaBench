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
 int /*<<< orphan*/  hevc_intra_pred_dc_16x16_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hevc_intra_pred_dc_32x32_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hevc_intra_pred_dc_4x4_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hevc_intra_pred_dc_8x8_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ff_hevc_intra_pred_dc_msa(uint8_t *dst, const uint8_t *src_top,
                               const uint8_t *src_left,
                               ptrdiff_t stride, int log2, int c_idx)
{
    switch (log2) {
    case 2:
        hevc_intra_pred_dc_4x4_msa(src_top, src_left, dst, stride, c_idx);
        break;

    case 3:
        hevc_intra_pred_dc_8x8_msa(src_top, src_left, dst, stride, c_idx);
        break;

    case 4:
        hevc_intra_pred_dc_16x16_msa(src_top, src_left, dst, stride, c_idx);
        break;

    case 5:
        hevc_intra_pred_dc_32x32_msa(src_top, src_left, dst, stride);
        break;
    }
}