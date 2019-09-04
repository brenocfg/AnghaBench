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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void gif_copy_img_rect(const uint32_t *src, uint32_t *dst,
                              int linesize, int l, int t, int w, int h)
{
    const int y_start = t * linesize;
    const uint32_t *src_px,
                   *src_py = src + y_start,
                   *dst_py = dst + y_start;
    const uint32_t *src_pb = src_py + h * linesize;
    uint32_t *dst_px;

    for (; src_py < src_pb; src_py += linesize, dst_py += linesize) {
        src_px = src_py + l;
        dst_px = (uint32_t *)dst_py + l;

        memcpy(dst_px, src_px, w * sizeof(uint32_t));
    }
}