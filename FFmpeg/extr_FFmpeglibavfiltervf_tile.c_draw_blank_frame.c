#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  current; int /*<<< orphan*/  blank; int /*<<< orphan*/  draw; } ;
typedef  TYPE_1__ TileContext ;
struct TYPE_11__ {TYPE_3__** inputs; TYPE_1__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_9__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_fill_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tile_pos (TYPE_4__*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_blank_frame(AVFilterContext *ctx, AVFrame *out_buf)
{
    TileContext *tile    = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    unsigned x0, y0;

    get_tile_pos(ctx, &x0, &y0, tile->current);
    ff_fill_rectangle(&tile->draw, &tile->blank,
                      out_buf->data, out_buf->linesize,
                      x0, y0, inlink->w, inlink->h);
    tile->current++;
}