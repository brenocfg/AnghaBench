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
struct TYPE_7__ {TYPE_1__* internal; } ;
struct TYPE_6__ {int /*<<< orphan*/  child_frames_ref; int /*<<< orphan*/  surfaces_internal; int /*<<< orphan*/  surface_ptrs; int /*<<< orphan*/  mem_ids; int /*<<< orphan*/  session_cond; int /*<<< orphan*/  session_lock; scalar_t__ session_upload_init; int /*<<< orphan*/ * session_upload; scalar_t__ session_download_init; int /*<<< orphan*/ * session_download; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ QSVFramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFXClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MFXVideoVPP_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->internal->priv;

    if (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = NULL;
    s->session_download_init = 0;

    if (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = NULL;
    s->session_upload_init = 0;

#if HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
    pthread_cond_destroy(&s->session_cond);
#endif

    av_freep(&s->mem_ids);
    av_freep(&s->surface_ptrs);
    av_freep(&s->surfaces_internal);
    av_buffer_unref(&s->child_frames_ref);
}