#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int x; int y; int* linesize; int h; int w; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ AVSubtitleRect ;

/* Variables and functions */

__attribute__((used)) static void copy_rectangle(AVSubtitleRect *dst, AVSubtitleRect *src, int cmap[])
{
    int x, y;
    uint8_t *p, *q;

    p = src->data[0];
    q = dst->data[0] + (src->x - dst->x) +
                            (src->y - dst->y) * dst->linesize[0];
    for (y = 0; y < src->h; y++) {
        for (x = 0; x < src->w; x++)
            *(q++) = cmap[*(p++)];
        p += src->linesize[0] - src->w;
        q += dst->linesize[0] - src->w;
    }
}