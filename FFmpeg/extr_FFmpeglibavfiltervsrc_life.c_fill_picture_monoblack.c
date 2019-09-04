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
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int* linesize; scalar_t__** data; } ;
struct TYPE_6__ {size_t buf_idx; int h; int w; scalar_t__** buf; } ;
typedef  TYPE_1__ LifeContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ ALIVE_CELL ; 

__attribute__((used)) static void fill_picture_monoblack(AVFilterContext *ctx, AVFrame *picref)
{
    LifeContext *life = ctx->priv;
    uint8_t *buf = life->buf[life->buf_idx];
    int i, j, k;

    /* fill the output picture with the old grid buffer */
    for (i = 0; i < life->h; i++) {
        uint8_t byte = 0;
        uint8_t *p = picref->data[0] + i * picref->linesize[0];
        for (k = 0, j = 0; j < life->w; j++) {
            byte |= (buf[i*life->w+j] == ALIVE_CELL)<<(7-k++);
            if (k==8 || j == life->w-1) {
                k = 0;
                *p++ = byte;
                byte = 0;
            }
        }
    }
}