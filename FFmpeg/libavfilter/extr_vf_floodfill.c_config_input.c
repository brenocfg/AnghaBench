#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {int w; int h; int /*<<< orphan*/  format; TYPE_5__* dst; } ;
struct TYPE_10__ {TYPE_1__* comp; } ;
struct TYPE_9__ {int nb_planes; int /*<<< orphan*/  points; scalar_t__ back; scalar_t__ front; int /*<<< orphan*/  pick_pixel; int /*<<< orphan*/  is_same; int /*<<< orphan*/  set_pixel; } ;
struct TYPE_8__ {int depth; } ;
typedef  int /*<<< orphan*/  Points ;
typedef  TYPE_2__ FloodfillContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_calloc (int,int) ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_same1 ; 
 int /*<<< orphan*/  is_same1_16 ; 
 int /*<<< orphan*/  is_same3 ; 
 int /*<<< orphan*/  is_same3_16 ; 
 int /*<<< orphan*/  is_same4 ; 
 int /*<<< orphan*/  is_same4_16 ; 
 int /*<<< orphan*/  pick_pixel1 ; 
 int /*<<< orphan*/  pick_pixel1_16 ; 
 int /*<<< orphan*/  pick_pixel3 ; 
 int /*<<< orphan*/  pick_pixel3_16 ; 
 int /*<<< orphan*/  pick_pixel4 ; 
 int /*<<< orphan*/  pick_pixel4_16 ; 
 int /*<<< orphan*/  set_pixel1 ; 
 int /*<<< orphan*/  set_pixel1_16 ; 
 int /*<<< orphan*/  set_pixel3 ; 
 int /*<<< orphan*/  set_pixel3_16 ; 
 int /*<<< orphan*/  set_pixel4 ; 
 int /*<<< orphan*/  set_pixel4_16 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    FloodfillContext *s = ctx->priv;
    int depth;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);
    depth = desc->comp[0].depth;
    if (depth == 8) {
        switch (s->nb_planes) {
        case 1: s->set_pixel  = set_pixel1;
                s->is_same    = is_same1;
                s->pick_pixel = pick_pixel1; break;
        case 3: s->set_pixel  = set_pixel3;
                s->is_same    = is_same3;
                s->pick_pixel = pick_pixel3; break;
        case 4: s->set_pixel  = set_pixel4;
                s->is_same    = is_same4;
                s->pick_pixel = pick_pixel4; break;
       }
    } else {
        switch (s->nb_planes) {
        case 1: s->set_pixel  = set_pixel1_16;
                s->is_same    = is_same1_16;
                s->pick_pixel = pick_pixel1_16; break;
        case 3: s->set_pixel  = set_pixel3_16;
                s->is_same    = is_same3_16;
                s->pick_pixel = pick_pixel3_16; break;
        case 4: s->set_pixel  = set_pixel4_16;
                s->is_same    = is_same4_16;
                s->pick_pixel = pick_pixel4_16; break;
       }
    }

    s->front = s->back = 0;
    s->points = av_calloc(inlink->w * inlink->h, 4 * sizeof(Points));
    if (!s->points)
        return AVERROR(ENOMEM);

    return 0;
}