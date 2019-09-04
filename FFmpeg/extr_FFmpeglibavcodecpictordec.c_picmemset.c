#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_6__ {unsigned int** data; int* linesize; } ;
struct TYPE_5__ {int width; int height; int nb_planes; } ;
typedef  TYPE_1__ PicContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void picmemset(PicContext *s, AVFrame *frame, unsigned value, int run,
                      int *x, int *y, int *plane, int bits_per_plane)
{
    uint8_t *d;
    int shift = *plane * bits_per_plane;
    unsigned mask  = ((1U << bits_per_plane) - 1) << shift;
    int xl = *x;
    int yl = *y;
    int planel = *plane;
    value   <<= shift;

    d = frame->data[0] + yl * frame->linesize[0];
    while (run > 0) {
        int j;
        for (j = 8-bits_per_plane; j >= 0; j -= bits_per_plane) {
            d[xl] |= (value >> j) & mask;
            xl += 1;
            if (xl == s->width) {
                yl -= 1;
                xl = 0;
                if (yl < 0) {
                   yl = s->height - 1;
                   planel += 1;
                   if (planel >= s->nb_planes)
                       goto end;
                   value <<= bits_per_plane;
                   mask  <<= bits_per_plane;
                }
                d = frame->data[0] + yl * frame->linesize[0];
            }
        }
        run--;
    }
end:
    *x = xl;
    *y = yl;
    *plane = planel;
}