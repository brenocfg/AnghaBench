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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 void* av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vector_clip_int32_c(int32_t *dst, const int32_t *src, int32_t min,
                                int32_t max, unsigned int len)
{
    do {
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        *dst++ = av_clip(*src++, min, max);
        len   -= 8;
    } while (len > 0);
}