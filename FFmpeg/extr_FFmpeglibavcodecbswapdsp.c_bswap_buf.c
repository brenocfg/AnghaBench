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
 int /*<<< orphan*/  av_bswap32 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void bswap_buf(uint32_t *dst, const uint32_t *src, int w)
{
    int i;

    for (i = 0; i + 8 <= w; i += 8) {
        dst[i + 0] = av_bswap32(src[i + 0]);
        dst[i + 1] = av_bswap32(src[i + 1]);
        dst[i + 2] = av_bswap32(src[i + 2]);
        dst[i + 3] = av_bswap32(src[i + 3]);
        dst[i + 4] = av_bswap32(src[i + 4]);
        dst[i + 5] = av_bswap32(src[i + 5]);
        dst[i + 6] = av_bswap32(src[i + 6]);
        dst[i + 7] = av_bswap32(src[i + 7]);
    }
    for (; i < w; i++)
        dst[i + 0] = av_bswap32(src[i + 0]);
}