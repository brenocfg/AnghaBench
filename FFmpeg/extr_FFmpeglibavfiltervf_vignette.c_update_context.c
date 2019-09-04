#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* fmap; int fmap_linesize; scalar_t__ backward; void* angle; int /*<<< orphan*/  eval_mode; void* y0; void* x0; void** var_values; int /*<<< orphan*/  y0_pexpr; int /*<<< orphan*/  x0_pexpr; int /*<<< orphan*/  angle_pexpr; } ;
typedef  TYPE_1__ VignetteContext ;
struct TYPE_10__ {int h; int w; int /*<<< orphan*/  time_base; void* frame_count_out; } ;
struct TYPE_9__ {int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  EVAL_MODE_FRAME ; 
 int /*<<< orphan*/  M_PI_2 ; 
 void* NAN ; 
 void* TS2D (int /*<<< orphan*/ ) ; 
 void* TS2T (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t VAR_N ; 
 size_t VAR_PTS ; 
 size_t VAR_T ; 
 void* av_clipf (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* av_expr_eval (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int get_natural_factor (TYPE_1__*,int,int) ; 
 scalar_t__ isnan (void*) ; 

__attribute__((used)) static void update_context(VignetteContext *s, AVFilterLink *inlink, AVFrame *frame)
{
    int x, y;
    float *dst = s->fmap;
    int dst_linesize = s->fmap_linesize;

    if (frame) {
        s->var_values[VAR_N]   = inlink->frame_count_out;
        s->var_values[VAR_T]   = TS2T(frame->pts, inlink->time_base);
        s->var_values[VAR_PTS] = TS2D(frame->pts);
    } else {
        s->var_values[VAR_N]   = NAN;
        s->var_values[VAR_T]   = NAN;
        s->var_values[VAR_PTS] = NAN;
    }

    s->angle = av_expr_eval(s->angle_pexpr, s->var_values, NULL);
    s->x0 = av_expr_eval(s->x0_pexpr, s->var_values, NULL);
    s->y0 = av_expr_eval(s->y0_pexpr, s->var_values, NULL);

    if (isnan(s->x0) || isnan(s->y0) || isnan(s->angle))
        s->eval_mode = EVAL_MODE_FRAME;

    s->angle = av_clipf(s->angle, 0, M_PI_2);

    if (s->backward) {
        for (y = 0; y < inlink->h; y++) {
            for (x = 0; x < inlink->w; x++)
                dst[x] = 1. / get_natural_factor(s, x, y);
            dst += dst_linesize;
        }
    } else {
        for (y = 0; y < inlink->h; y++) {
            for (x = 0; x < inlink->w; x++)
                dst[x] = get_natural_factor(s, x, y);
            dst += dst_linesize;
        }
    }
}