#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int vscroll; int hscroll; TYPE_1__* frame; } ;
struct TYPE_4__ {int* linesize; int** data; } ;
typedef  TYPE_2__ CDGraphicsContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CDG_FULL_HEIGHT ; 
 int CDG_FULL_WIDTH ; 
 int CDG_TILE_HEIGHT ; 
 int CDG_TILE_WIDTH ; 
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static int cdg_tile_block(CDGraphicsContext *cc, uint8_t *data, int b)
{
    unsigned ci, ri;
    int color;
    int x, y;
    int ai;
    int stride   = cc->frame->linesize[0];
    uint8_t *buf = cc->frame->data[0];

    ri = (data[2] & 0x1F) * CDG_TILE_HEIGHT + cc->vscroll;
    ci = (data[3] & 0x3F) * CDG_TILE_WIDTH  + cc->hscroll;

    if (ri > (CDG_FULL_HEIGHT - CDG_TILE_HEIGHT))
        return AVERROR(EINVAL);
    if (ci > (CDG_FULL_WIDTH - CDG_TILE_WIDTH))
        return AVERROR(EINVAL);

    for (y = 0; y < CDG_TILE_HEIGHT; y++) {
        for (x = 0; x < CDG_TILE_WIDTH; x++) {
            if (!((data[4 + y] >> (5 - x)) & 0x01))
                color = data[0] & 0x0F;
            else
                color = data[1] & 0x0F;

            ai = ci + x + (stride * (ri + y));
            if (b)
                color ^= buf[ai];
            buf[ai] = color;
        }
    }

    return 0;
}