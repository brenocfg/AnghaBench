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
typedef  int uint8_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int** data; int* linesize; } ;
struct TYPE_6__ {int** buf; size_t buf_idx; int h; int w; int mold; int* mold_color; int* death_color; int* life_color; } ;
typedef  TYPE_1__ LifeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int ALIVE_CELL ; 
 int /*<<< orphan*/  AV_WB24 (int*,int const) ; 
 void* FAST_DIV255 (int const) ; 
 int FFMIN (int,int) ; 

__attribute__((used)) static void fill_picture_rgb(AVFilterContext *ctx, AVFrame *picref)
{
    LifeContext *life = ctx->priv;
    uint8_t *buf = life->buf[life->buf_idx];
    int i, j;

    /* fill the output picture with the old grid buffer */
    for (i = 0; i < life->h; i++) {
        uint8_t *p = picref->data[0] + i * picref->linesize[0];
        for (j = 0; j < life->w; j++) {
            uint8_t v = buf[i*life->w + j];
            if (life->mold && v != ALIVE_CELL) {
                const uint8_t *c1 = life-> mold_color;
                const uint8_t *c2 = life->death_color;
                int death_age = FFMIN((0xff - v) * life->mold, 0xff);
                *p++ = FAST_DIV255((c2[0] << 8) + ((int)c1[0] - (int)c2[0]) * death_age);
                *p++ = FAST_DIV255((c2[1] << 8) + ((int)c1[1] - (int)c2[1]) * death_age);
                *p++ = FAST_DIV255((c2[2] << 8) + ((int)c1[2] - (int)c2[2]) * death_age);
            } else {
                const uint8_t *c = v == ALIVE_CELL ? life->life_color : life->death_color;
                AV_WB24(p, c[0]<<16 | c[1]<<8 | c[2]);
                p += 3;
            }
        }
    }
}