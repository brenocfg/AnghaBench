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
 size_t av_clip_uint8 (int) ; 
 float* ff_vorbis_floor1_inverse_db_table ; 

__attribute__((used)) static inline void render_line_unrolled(intptr_t x, int y, int x1,
                                        intptr_t sy, int ady, int adx,
                                        float *buf)
{
    int err = -adx;
    x -= x1 - 1;
    buf += x1 - 1;
    while (++x < 0) {
        err += ady;
        if (err >= 0) {
            err += ady - adx;
            y   += sy;
            buf[x++] = ff_vorbis_floor1_inverse_db_table[av_clip_uint8(y)];
        }
        buf[x] = ff_vorbis_floor1_inverse_db_table[av_clip_uint8(y)];
    }
    if (x <= 0) {
        if (err + ady >= 0)
            y += sy;
        buf[x] = ff_vorbis_floor1_inverse_db_table[av_clip_uint8(y)];
    }
}