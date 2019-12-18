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
struct TYPE_11__ {TYPE_1__* internal; TYPE_3__** outputs; TYPE_2__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  h; } ;
struct TYPE_9__ {scalar_t__ pos_x; scalar_t__ dest_x; scalar_t__ pos_y; scalar_t__ dest_y; int jump; int /*<<< orphan*/  draw_slice; int /*<<< orphan*/  lfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* execute ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SierpinskiContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_sierpinski(AVFilterContext *ctx, AVFrame *frame)
{
    SierpinskiContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    if (s->pos_x == s->dest_x && s->pos_y == s->dest_y) {
        unsigned int rnd = av_lfg_get(&s->lfg);
        int mod = 2 * s->jump + 1;

        s->dest_x += (int)((rnd & 0xffff) % mod) - s->jump;
        s->dest_y += (int)((rnd >>    16) % mod) - s->jump;
    } else {
        if (s->pos_x < s->dest_x)
            s->pos_x++;
        else if (s->pos_x > s->dest_x)
            s->pos_x--;

        if (s->pos_y < s->dest_y)
            s->pos_y++;
        else if (s->pos_y > s->dest_y)
            s->pos_y--;
    }

    ctx->internal->execute(ctx, s->draw_slice, frame, NULL, FFMIN(outlink->h, ff_filter_get_nb_threads(ctx)));
}