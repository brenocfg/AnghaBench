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
typedef  int uint16_t ;
struct TYPE_3__ {int depth; int pixel_depth; int*** plane; int linesize; } ;
typedef  TYPE_1__ OWDenoiseContext ;

/* Variables and functions */
 int /*<<< orphan*/  compose2D2 (double*,double**,double**,int,int,int,int) ; 
 int /*<<< orphan*/  decompose2D2 (int**,int*,int**,int,int,int,int) ; 
 double** dither ; 

__attribute__((used)) static void filter(OWDenoiseContext *s,
                   uint8_t       *dst, int dst_linesize,
                   const uint8_t *src, int src_linesize,
                   int width, int height, double strength)
{
    int x, y, i, j, depth = s->depth;

    while (1<<depth > width || 1<<depth > height)
        depth--;

    if (s->pixel_depth <= 8) {
        for (y = 0; y < height; y++)
            for(x = 0; x < width; x++)
                s->plane[0][0][y*s->linesize + x] = src[y*src_linesize + x];
    } else {
        const uint16_t *src16 = (const uint16_t *)src;

        src_linesize /= 2;
        for (y = 0; y < height; y++)
            for(x = 0; x < width; x++)
                s->plane[0][0][y*s->linesize + x] = src16[y*src_linesize + x];
    }

    for (i = 0; i < depth; i++)
        decompose2D2(s->plane[i + 1], s->plane[i][0], s->plane[0] + 1, s->linesize, 1<<i, width, height);

    for (i = 0; i < depth; i++) {
        for (j = 1; j < 4; j++) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    double v = s->plane[i + 1][j][y*s->linesize + x];
                    if      (v >  strength) v -= strength;
                    else if (v < -strength) v += strength;
                    else                    v  = 0;
                    s->plane[i + 1][j][x + y*s->linesize] = v;
                }
            }
        }
    }
    for (i = depth-1; i >= 0; i--)
        compose2D2(s->plane[i][0], s->plane[i + 1], s->plane[0] + 1, s->linesize, 1<<i, width, height);

    if (s->pixel_depth <= 8) {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                i = s->plane[0][0][y*s->linesize + x] + dither[x&7][y&7]*(1.0/64) + 1.0/128; // yes the rounding is insane but optimal :)
                if ((unsigned)i > 255U) i = ~(i >> 31);
                dst[y*dst_linesize + x] = i;
            }
        }
    } else {
        uint16_t *dst16 = (uint16_t *)dst;

        dst_linesize /= 2;
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                i = s->plane[0][0][y*s->linesize + x];
                dst16[y*dst_linesize + x] = i;
            }
        }
    }
}