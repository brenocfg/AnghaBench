#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {scalar_t__ height; int width; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {double prev_mafd; TYPE_2__* prev_picref; int /*<<< orphan*/  (* sad ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__*) ;} ;
typedef  TYPE_1__ SelectContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int FFMIN (double,double) ; 
 double av_clipf (int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* av_frame_clone (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  emms_c () ; 
 double fabs (double) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static double get_scene_score(AVFilterContext *ctx, AVFrame *frame)
{
    double ret = 0;
    SelectContext *select = ctx->priv;
    AVFrame *prev_picref = select->prev_picref;

    if (prev_picref &&
        frame->height == prev_picref->height &&
        frame->width  == prev_picref->width) {
        uint64_t sad;
        double mafd, diff;

        select->sad(prev_picref->data[0], prev_picref->linesize[0], frame->data[0], frame->linesize[0], frame->width * 3, frame->height, &sad);
        emms_c();
        mafd = (double)sad / (frame->width * 3 * frame->height);
        diff = fabs(mafd - select->prev_mafd);
        ret  = av_clipf(FFMIN(mafd, diff) / 100., 0, 1);
        select->prev_mafd = mafd;
        av_frame_free(&prev_picref);
    }
    select->prev_picref = av_frame_clone(frame);
    return ret;
}