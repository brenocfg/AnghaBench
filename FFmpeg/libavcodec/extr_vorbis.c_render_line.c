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

/* Variables and functions */
 int FFABS (int) ; 
 size_t av_clip_uint8 (int) ; 
 float* ff_vorbis_floor1_inverse_db_table ; 
 int /*<<< orphan*/  render_line_unrolled (int,int,int,int,int,int,float*) ; 

__attribute__((used)) static void render_line(int x0, int y0, int x1, int y1, float *buf)
{
    int dy  = y1 - y0;
    int adx = x1 - x0;
    int ady = FFABS(dy);
    int sy  = dy < 0 ? -1 : 1;
    buf[x0] = ff_vorbis_floor1_inverse_db_table[av_clip_uint8(y0)];
    if (ady*2 <= adx) { // optimized common case
        render_line_unrolled(x0, y0, x1, sy, ady, adx, buf);
    } else {
        int base  = dy / adx;
        int x     = x0;
        int y     = y0;
        int err   = -adx;
        ady -= FFABS(base) * adx;
        while (++x < x1) {
            y += base;
            err += ady;
            if (err >= 0) {
                err -= adx;
                y   += sy;
            }
            buf[x] = ff_vorbis_floor1_inverse_db_table[av_clip_uint8(y)];
        }
    }
}