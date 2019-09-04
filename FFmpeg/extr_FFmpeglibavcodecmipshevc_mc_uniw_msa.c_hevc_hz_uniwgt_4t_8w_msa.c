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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hevc_hz_uniwgt_4t_8x2_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  hevc_hz_uniwgt_4t_8x4_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  hevc_hz_uniwgt_4t_8x6_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  hevc_hz_uniwgt_4t_8x8multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,int,int) ; 

__attribute__((used)) static void hevc_hz_uniwgt_4t_8w_msa(uint8_t *src,
                                     int32_t src_stride,
                                     uint8_t *dst,
                                     int32_t dst_stride,
                                     const int8_t *filter,
                                     int32_t height,
                                     int32_t weight,
                                     int32_t offset,
                                     int32_t rnd_val)
{
    if (2 == height) {
        hevc_hz_uniwgt_4t_8x2_msa(src, src_stride, dst, dst_stride,
                                  filter, weight, offset, rnd_val);
    } else if (4 == height) {
        hevc_hz_uniwgt_4t_8x4_msa(src, src_stride, dst, dst_stride,
                                  filter, weight, offset, rnd_val);
    } else if (6 == height) {
        hevc_hz_uniwgt_4t_8x6_msa(src, src_stride, dst, dst_stride,
                                  filter, weight, offset, rnd_val);
    } else {
        hevc_hz_uniwgt_4t_8x8multiple_msa(src, src_stride, dst, dst_stride,
                                          filter, height, weight, offset,
                                          rnd_val);
    }
}