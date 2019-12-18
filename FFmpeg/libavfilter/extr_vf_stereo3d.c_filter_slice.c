#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* out; TYPE_6__* iright; TYPE_6__* ileft; } ;
typedef  TYPE_4__ ThreadData ;
struct TYPE_15__ {TYPE_5__* priv; } ;
struct TYPE_14__ {int* linesize; scalar_t__* data; } ;
struct TYPE_11__ {int height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {int row_step; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* anaglyph ) (scalar_t__,scalar_t__,scalar_t__,int,int,int,int /*<<< orphan*/ ,int,int const*,int const*,int const*) ;} ;
struct TYPE_13__ {int** ana_matrix; TYPE_3__ out; TYPE_2__ in; scalar_t__* in_off_right; scalar_t__* in_off_left; TYPE_1__ dsp; } ;
typedef  TYPE_5__ Stereo3DContext ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,scalar_t__,int,int,int,int /*<<< orphan*/ ,int,int const*,int const*,int const*) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    Stereo3DContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *ileft = td->ileft;
    AVFrame *iright = td->iright;
    AVFrame *out = td->out;
    int height = s->out.height;
    int start = (height *  jobnr   ) / nb_jobs;
    int end   = (height * (jobnr+1)) / nb_jobs;
    const int **ana_matrix = s->ana_matrix;

    s->dsp.anaglyph(out->data[0] + out->linesize[0] * start,
             ileft ->data[0] + s->in_off_left [0]  + ileft->linesize[0] * start * s->in.row_step,
             iright->data[0] + s->in_off_right[0] + iright->linesize[0] * start * s->in.row_step,
             out->linesize[0],
             ileft->linesize[0] * s->in.row_step,
             iright->linesize[0] * s->in.row_step,
             s->out.width, end - start,
             ana_matrix[0], ana_matrix[1], ana_matrix[2]);

    return 0;
}