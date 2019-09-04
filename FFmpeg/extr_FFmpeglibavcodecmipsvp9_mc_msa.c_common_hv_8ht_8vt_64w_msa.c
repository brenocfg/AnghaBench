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
 int /*<<< orphan*/  common_hv_8ht_8vt_8w_msa (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void common_hv_8ht_8vt_64w_msa(const uint8_t *src, int32_t src_stride,
                                      uint8_t *dst, int32_t dst_stride,
                                      const int8_t *filter_horiz,
                                      const int8_t *filter_vert,
                                      int32_t height)
{
    int32_t multiple8_cnt;

    for (multiple8_cnt = 8; multiple8_cnt--;) {
        common_hv_8ht_8vt_8w_msa(src, src_stride, dst, dst_stride, filter_horiz,
                                 filter_vert, height);

        src += 8;
        dst += 8;
    }
}