#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* buf; TYPE_1__* sys; } ;
struct TYPE_7__ {int* mb_coordinates; } ;
struct TYPE_6__ {int height; } ;
typedef  TYPE_2__ DVwork_chunk ;
typedef  TYPE_3__ DVVideoContext ;

/* Variables and functions */

__attribute__((used)) static inline void dv_calculate_mb_xy(DVVideoContext *s,
                                      DVwork_chunk *work_chunk,
                                      int m, int *mb_x, int *mb_y)
{
    *mb_x = work_chunk->mb_coordinates[m] & 0xff;
    *mb_y = work_chunk->mb_coordinates[m] >> 8;

    /* We work with 720p frames split in half.
     * The odd half-frame (chan == 2,3) is displaced :-( */
    if (s->sys->height == 720 && !(s->buf[1] & 0x0C))
        /* shifting the Y coordinate down by 72/2 macro blocks */
        *mb_y -= (*mb_y > 17) ? 18 : -72;
}