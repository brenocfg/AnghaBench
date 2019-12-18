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
struct TYPE_8__ {int w; int h; TYPE_1__* dst; } ;
struct TYPE_7__ {int x; int band; int w; int y; int h; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ DelogoContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    DelogoContext *s = inlink->dst->priv;

    /* Check whether the logo area fits in the frame */
    if (s->x + (s->band - 1) < 0 || s->x + s->w - (s->band*2 - 2) > inlink->w ||
        s->y + (s->band - 1) < 0 || s->y + s->h - (s->band*2 - 2) > inlink->h) {
        av_log(s, AV_LOG_ERROR, "Logo area is outside of the frame.\n");
        return AVERROR(EINVAL);
    }

    return 0;
}