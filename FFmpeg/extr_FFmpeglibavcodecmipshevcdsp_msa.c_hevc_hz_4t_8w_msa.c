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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  hevc_hz_4t_8x2multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  hevc_hz_4t_8x4multiple_msa (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void hevc_hz_4t_8w_msa(uint8_t *src,
                              int32_t src_stride,
                              int16_t *dst,
                              int32_t dst_stride,
                              const int8_t *filter,
                              int32_t height)
{
    if (2 == height || 6 == height) {
        hevc_hz_4t_8x2multiple_msa(src, src_stride, dst, dst_stride,
                                   filter, height);
    } else {
        hevc_hz_4t_8x4multiple_msa(src, src_stride, dst, dst_stride,
                                   filter, height);
    }
}