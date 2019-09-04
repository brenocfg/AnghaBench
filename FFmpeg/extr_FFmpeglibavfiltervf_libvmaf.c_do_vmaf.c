#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct TYPE_7__ {int frame_set; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  gmain; int /*<<< orphan*/  gref; scalar_t__ error; } ;
typedef  TYPE_1__ LIBVMAFContext ;
typedef  TYPE_2__ FFFrameSync ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_frame_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_framesync_dualinput_get (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_vmaf(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    LIBVMAFContext *s = ctx->priv;
    AVFrame *master, *ref;
    int ret;

    ret = ff_framesync_dualinput_get(fs, &master, &ref);
    if (ret < 0)
        return ret;
    if (!ref)
        return ff_filter_frame(ctx->outputs[0], master);

    pthread_mutex_lock(&s->lock);

    while (s->frame_set && !s->error) {
        pthread_cond_wait(&s->cond, &s->lock);
    }

    if (s->error) {
        av_log(ctx, AV_LOG_ERROR,
               "libvmaf encountered an error, check log for details\n");
        pthread_mutex_unlock(&s->lock);
        return AVERROR(EINVAL);
    }

    av_frame_ref(s->gref, ref);
    av_frame_ref(s->gmain, master);

    s->frame_set = 1;

    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);

    return ff_filter_frame(ctx->outputs[0], master);
}