#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double h; scalar_t__ w; int /*<<< orphan*/  format; TYPE_1__* dst; } ;
struct TYPE_6__ {double original_h; int shaping; int /*<<< orphan*/  renderer; scalar_t__ original_w; scalar_t__ alpha; int /*<<< orphan*/  draw; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ AssContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  FF_DRAW_PROCESS_ALPHA ; 
 int /*<<< orphan*/  ass_set_aspect_ratio (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  ass_set_frame_size (int /*<<< orphan*/ ,scalar_t__,double) ; 
 int /*<<< orphan*/  ass_set_shaper (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_draw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AssContext *ass = inlink->dst->priv;

    ff_draw_init(&ass->draw, inlink->format, ass->alpha ? FF_DRAW_PROCESS_ALPHA : 0);

    ass_set_frame_size  (ass->renderer, inlink->w, inlink->h);
    if (ass->original_w && ass->original_h)
        ass_set_aspect_ratio(ass->renderer, (double)inlink->w / inlink->h,
                             (double)ass->original_w / ass->original_h);
    if (ass->shaping != -1)
        ass_set_shaper(ass->renderer, ass->shaping);

    return 0;
}