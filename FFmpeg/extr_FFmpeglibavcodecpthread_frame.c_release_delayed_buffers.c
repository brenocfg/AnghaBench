#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  extended_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_mutex; } ;
struct TYPE_8__ {size_t num_released_buffers; TYPE_4__* released_buffers; TYPE_1__* avctx; TYPE_3__* parent; } ;
struct TYPE_7__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ PerThreadContext ;
typedef  TYPE_3__ FrameThreadContext ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_delayed_buffers(PerThreadContext *p)
{
    FrameThreadContext *fctx = p->parent;

    while (p->num_released_buffers > 0) {
        AVFrame *f;

        pthread_mutex_lock(&fctx->buffer_mutex);

        // fix extended data in case the caller screwed it up
        av_assert0(p->avctx->codec_type == AVMEDIA_TYPE_VIDEO ||
                   p->avctx->codec_type == AVMEDIA_TYPE_AUDIO);
        f = &p->released_buffers[--p->num_released_buffers];
        f->extended_data = f->data;
        av_frame_unref(f);

        pthread_mutex_unlock(&fctx->buffer_mutex);
    }
}