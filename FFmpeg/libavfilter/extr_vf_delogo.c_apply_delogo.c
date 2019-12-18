#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int den; int num; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 void* FFMAX (unsigned int,int) ; 
 int /*<<< orphan*/  av_image_copy_plane (int*,int,int*,int,int,int) ; 

__attribute__((used)) static void apply_delogo(uint8_t *dst, int dst_linesize,
                         uint8_t *src, int src_linesize,
                         int w, int h, AVRational sar,
                         int logo_x, int logo_y, int logo_w, int logo_h,
                         unsigned int band, int show, int direct)
{
    int x, y;
    uint64_t interp, weightl, weightr, weightt, weightb, weight;
    uint8_t *xdst, *xsrc;

    uint8_t *topleft, *botleft, *topright;
    unsigned int left_sample, right_sample;
    int xclipl, xclipr, yclipt, yclipb;
    int logo_x1, logo_x2, logo_y1, logo_y2;

    xclipl = FFMAX(-logo_x, 0);
    xclipr = FFMAX(logo_x+logo_w-w, 0);
    yclipt = FFMAX(-logo_y, 0);
    yclipb = FFMAX(logo_y+logo_h-h, 0);

    logo_x1 = logo_x + xclipl;
    logo_x2 = logo_x + logo_w - xclipr - 1;
    logo_y1 = logo_y + yclipt;
    logo_y2 = logo_y + logo_h - yclipb - 1;

    topleft  = src+logo_y1 * src_linesize+logo_x1;
    topright = src+logo_y1 * src_linesize+logo_x2;
    botleft  = src+logo_y2 * src_linesize+logo_x1;

    if (!direct)
        av_image_copy_plane(dst, dst_linesize, src, src_linesize, w, h);

    dst += (logo_y1 + 1) * dst_linesize;
    src += (logo_y1 + 1) * src_linesize;

    for (y = logo_y1+1; y < logo_y2; y++) {
        left_sample = topleft[src_linesize*(y-logo_y1)]   +
                      topleft[src_linesize*(y-logo_y1-1)] +
                      topleft[src_linesize*(y-logo_y1+1)];
        right_sample = topright[src_linesize*(y-logo_y1)]   +
                       topright[src_linesize*(y-logo_y1-1)] +
                       topright[src_linesize*(y-logo_y1+1)];

        for (x = logo_x1+1,
             xdst = dst+logo_x1+1,
             xsrc = src+logo_x1+1; x < logo_x2; x++, xdst++, xsrc++) {

            if (show && (y == logo_y1+1 || y == logo_y2-1 ||
                         x == logo_x1+1 || x == logo_x2-1)) {
                *xdst = 0;
                continue;
            }

            /* Weighted interpolation based on relative distances, taking SAR into account */
            weightl = (uint64_t)              (logo_x2-x) * (y-logo_y1) * (logo_y2-y) * sar.den;
            weightr = (uint64_t)(x-logo_x1)               * (y-logo_y1) * (logo_y2-y) * sar.den;
            weightt = (uint64_t)(x-logo_x1) * (logo_x2-x)               * (logo_y2-y) * sar.num;
            weightb = (uint64_t)(x-logo_x1) * (logo_x2-x) * (y-logo_y1)               * sar.num;

            interp =
                left_sample * weightl
                +
                right_sample * weightr
                +
                (topleft[x-logo_x1]    +
                 topleft[x-logo_x1-1]  +
                 topleft[x-logo_x1+1]) * weightt
                +
                (botleft[x-logo_x1]    +
                 botleft[x-logo_x1-1]  +
                 botleft[x-logo_x1+1]) * weightb;
            weight = (weightl + weightr + weightt + weightb) * 3U;
            interp = (interp + (weight >> 1)) / weight;

            if (y >= logo_y+band && y < logo_y+logo_h-band &&
                x >= logo_x+band && x < logo_x+logo_w-band) {
                *xdst = interp;
            } else {
                unsigned dist = 0;

                if      (x < logo_x+band)
                    dist = FFMAX(dist, logo_x-x+band);
                else if (x >= logo_x+logo_w-band)
                    dist = FFMAX(dist, x-(logo_x+logo_w-1-band));

                if      (y < logo_y+band)
                    dist = FFMAX(dist, logo_y-y+band);
                else if (y >= logo_y+logo_h-band)
                    dist = FFMAX(dist, y-(logo_y+logo_h-1-band));

                *xdst = (*xsrc*dist + interp*(band-dist))/band;
            }
        }

        dst += dst_linesize;
        src += src_linesize;
    }
}