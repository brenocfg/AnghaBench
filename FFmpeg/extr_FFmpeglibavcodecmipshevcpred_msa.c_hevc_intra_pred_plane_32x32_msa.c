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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  process_intra_lower_16x16_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  process_intra_upper_16x16_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void hevc_intra_pred_plane_32x32_msa(const uint8_t *src_top,
                                            const uint8_t *src_left,
                                            uint8_t *dst, int32_t stride)
{
    process_intra_upper_16x16_msa(src_top, src_left, dst, stride, 0);
    process_intra_upper_16x16_msa((src_top + 16), src_left,
                                  (dst + 16), stride, 16);
    dst += (16 * stride);
    src_left += 16;

    process_intra_lower_16x16_msa(src_top, src_left, dst, stride, 0);
    process_intra_lower_16x16_msa((src_top + 16), src_left,
                                  (dst + 16), stride, 16);
}