#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int h; size_t plane; double w; TYPE_6__* param; TYPE_4__* dst; TYPE_3__* bottom; TYPE_2__* top; TYPE_1__* inlink; } ;
typedef  TYPE_5__ ThreadData ;
struct TYPE_12__ {int /*<<< orphan*/  (* blend ) (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,double,int,TYPE_6__*,double*,int) ;} ;
struct TYPE_10__ {double pts; int* linesize; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {double frame_count_out; int /*<<< orphan*/  time_base; } ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 double AV_NOPTS_VALUE ; 
 double NAN ; 
 size_t VAR_H ; 
 size_t VAR_N ; 
 size_t VAR_SH ; 
 size_t VAR_SW ; 
 size_t VAR_T ; 
 int VAR_VARS_NB ; 
 size_t VAR_W ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,double,int,TYPE_6__*,double*,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ThreadData *td = arg;
    int slice_start = (td->h *  jobnr   ) / nb_jobs;
    int slice_end   = (td->h * (jobnr+1)) / nb_jobs;
    int height      = slice_end - slice_start;
    const uint8_t *top    = td->top->data[td->plane];
    const uint8_t *bottom = td->bottom->data[td->plane];
    uint8_t *dst    = td->dst->data[td->plane];
    double values[VAR_VARS_NB];

    values[VAR_N]  = td->inlink->frame_count_out;
    values[VAR_T]  = td->dst->pts == AV_NOPTS_VALUE ? NAN : td->dst->pts * av_q2d(td->inlink->time_base);
    values[VAR_W]  = td->w;
    values[VAR_H]  = td->h;
    values[VAR_SW] = td->w / (double)td->dst->width;
    values[VAR_SH] = td->h / (double)td->dst->height;

    td->param->blend(top + slice_start * td->top->linesize[td->plane],
                     td->top->linesize[td->plane],
                     bottom + slice_start * td->bottom->linesize[td->plane],
                     td->bottom->linesize[td->plane],
                     dst + slice_start * td->dst->linesize[td->plane],
                     td->dst->linesize[td->plane],
                     td->w, height, td->param, &values[0], slice_start);
    return 0;
}