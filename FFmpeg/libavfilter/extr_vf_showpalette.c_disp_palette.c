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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static int disp_palette(AVFrame *out, const AVFrame *in, int size)
{
    int x, y, i, j;
    uint32_t *dst = (uint32_t *)out->data[0];
    const int dst_linesize = out->linesize[0] >> 2;
    const uint32_t *pal = (uint32_t *)in->data[1];

    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++)
            for (j = 0; j < size; j++)
                for (i = 0; i < size; i++)
                    dst[(y*dst_linesize + x) * size + j*dst_linesize + i] = pal[y*16 + x];
    return 0;
}