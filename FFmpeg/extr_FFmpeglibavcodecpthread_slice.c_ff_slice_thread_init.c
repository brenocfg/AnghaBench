#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int caps_internal; } ;
struct TYPE_11__ {int thread_count; scalar_t__ codec_id; int height; int /*<<< orphan*/  execute2; int /*<<< orphan*/  execute; scalar_t__ active_thread_type; TYPE_1__* internal; TYPE_8__* codec; } ;
struct TYPE_10__ {int /*<<< orphan*/  thread; } ;
struct TYPE_9__ {TYPE_2__* thread_ctx; } ;
typedef  TYPE_2__ SliceThreadContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG1VIDEO ; 
 void* FFMIN (int,int) ; 
 int FF_CODEC_CAP_SLICE_THREAD_HAS_MF ; 
 int MAX_AUTO_THREADS ; 
 scalar_t__ av_codec_is_encoder (TYPE_8__*) ; 
 int av_cpu_count () ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 TYPE_2__* av_mallocz (int) ; 
 int avpriv_slicethread_create (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,void (*) (void*),int) ; 
 int /*<<< orphan*/  avpriv_slicethread_free (int /*<<< orphan*/ *) ; 
 void main_function (void*) ; 
 int /*<<< orphan*/  thread_execute ; 
 int /*<<< orphan*/  thread_execute2 ; 
 int /*<<< orphan*/  worker_func ; 

int ff_slice_thread_init(AVCodecContext *avctx)
{
    SliceThreadContext *c;
    int thread_count = avctx->thread_count;
    static void (*mainfunc)(void *);

    // We cannot do this in the encoder init as the threads are created before
    if (av_codec_is_encoder(avctx->codec) &&
        avctx->codec_id == AV_CODEC_ID_MPEG1VIDEO &&
        avctx->height > 2800)
        thread_count = avctx->thread_count = 1;

    if (!thread_count) {
        int nb_cpus = av_cpu_count();
        if  (avctx->height)
            nb_cpus = FFMIN(nb_cpus, (avctx->height+15)/16);
        // use number of cores + 1 as thread count if there is more than one
        if (nb_cpus > 1)
            thread_count = avctx->thread_count = FFMIN(nb_cpus + 1, MAX_AUTO_THREADS);
        else
            thread_count = avctx->thread_count = 1;
    }

    if (thread_count <= 1) {
        avctx->active_thread_type = 0;
        return 0;
    }

    avctx->internal->thread_ctx = c = av_mallocz(sizeof(*c));
    mainfunc = avctx->codec->caps_internal & FF_CODEC_CAP_SLICE_THREAD_HAS_MF ? &main_function : NULL;
    if (!c || (thread_count = avpriv_slicethread_create(&c->thread, avctx, worker_func, mainfunc, thread_count)) <= 1) {
        if (c)
            avpriv_slicethread_free(&c->thread);
        av_freep(&avctx->internal->thread_ctx);
        avctx->thread_count = 1;
        avctx->active_thread_type = 0;
        return 0;
    }
    avctx->thread_count = thread_count;

    avctx->execute = thread_execute;
    avctx->execute2 = thread_execute2;
    return 0;
}