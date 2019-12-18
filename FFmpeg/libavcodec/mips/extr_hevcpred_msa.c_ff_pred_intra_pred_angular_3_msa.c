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
 int /*<<< orphan*/  hevc_intra_pred_angular_lower_32width_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hevc_intra_pred_angular_upper_32width_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hevc_intra_pred_horiz_32x32_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intra_predict_vert_32x32_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ff_pred_intra_pred_angular_3_msa(uint8_t *dst,
                                      const uint8_t *src_top,
                                      const uint8_t *src_left,
                                      ptrdiff_t stride, int c_idx, int mode)
{
    if (mode == 10) {
        hevc_intra_pred_horiz_32x32_msa(src_top, src_left, dst, stride);
    } else if (mode == 26) {
        intra_predict_vert_32x32_msa(src_top, dst, stride);
    } else if (mode >= 18) {
        hevc_intra_pred_angular_upper_32width_msa(src_top, src_left,
                                                  dst, stride, mode);
    } else {
        hevc_intra_pred_angular_lower_32width_msa(src_top, src_left,
                                                  dst, stride, mode);
    }
}