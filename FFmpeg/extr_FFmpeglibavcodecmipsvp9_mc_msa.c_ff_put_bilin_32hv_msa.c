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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_put_bilin_16hv_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int,int) ; 

void ff_put_bilin_32hv_msa(uint8_t *dst, ptrdiff_t dst_stride,
                           const uint8_t *src, ptrdiff_t src_stride,
                           int height, int mx, int my)
{
    int32_t multiple8_cnt;

    for (multiple8_cnt = 2; multiple8_cnt--;) {
        ff_put_bilin_16hv_msa(dst, dst_stride, src, src_stride, height, mx, my);

        src += 16;
        dst += 16;
    }
}