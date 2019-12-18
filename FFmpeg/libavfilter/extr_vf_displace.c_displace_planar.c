#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int nb_planes; int* height; int* width; int edge; int /*<<< orphan*/ * blank; } ;
typedef  TYPE_1__ DisplaceContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
#define  EDGE_BLANK 131 
#define  EDGE_MIRROR 130 
#define  EDGE_SMEAR 129 
#define  EDGE_WRAP 128 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void displace_planar(DisplaceContext *s, const AVFrame *in,
                            const AVFrame *xpic, const AVFrame *ypic,
                            AVFrame *out)
{
    int plane, x, y;

    for (plane = 0; plane < s->nb_planes; plane++) {
        const int h = s->height[plane];
        const int w = s->width[plane];
        const int dlinesize = out->linesize[plane];
        const int slinesize = in->linesize[plane];
        const int xlinesize = xpic->linesize[plane];
        const int ylinesize = ypic->linesize[plane];
        const uint8_t *src = in->data[plane];
        const uint8_t *ysrc = ypic->data[plane];
        const uint8_t *xsrc = xpic->data[plane];
        uint8_t *dst = out->data[plane];
        const uint8_t blank = s->blank[plane];

        for (y = 0; y < h; y++) {
            switch (s->edge) {
            case EDGE_BLANK:
                for (x = 0; x < w; x++) {
                    int Y = y + ysrc[x] - 128;
                    int X = x + xsrc[x] - 128;

                    if (Y < 0 || Y >= h || X < 0 || X >= w)
                        dst[x] = blank;
                    else
                        dst[x] = src[Y * slinesize + X];
                }
                break;
            case EDGE_SMEAR:
                for (x = 0; x < w; x++) {
                    int Y = av_clip(y + ysrc[x] - 128, 0, h - 1);
                    int X = av_clip(x + xsrc[x] - 128, 0, w - 1);
                    dst[x] = src[Y * slinesize + X];
                }
                break;
            case EDGE_WRAP:
                for (x = 0; x < w; x++) {
                    int Y = (y + ysrc[x] - 128) % h;
                    int X = (x + xsrc[x] - 128) % w;

                    if (Y < 0)
                        Y += h;
                    if (X < 0)
                        X += w;
                    dst[x] = src[Y * slinesize + X];
                }
                break;
            case EDGE_MIRROR:
                for (x = 0; x < w; x++) {
                    int Y = y + ysrc[x] - 128;
                    int X = x + xsrc[x] - 128;

                    if (Y < 0)
                        Y = (-Y) % h;
                    if (X < 0)
                        X = (-X) % w;
                    if (Y >= h)
                        Y = h - (Y % h) - 1;
                    if (X >= w)
                        X = w - (X % w) - 1;
                    dst[x] = src[Y * slinesize + X];
                }
                break;
            }

            ysrc += ylinesize;
            xsrc += xlinesize;
            dst  += dlinesize;
        }
    }
}