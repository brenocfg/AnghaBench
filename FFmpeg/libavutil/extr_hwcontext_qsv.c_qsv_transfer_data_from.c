#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * mfxSyncPoint ;
typedef  scalar_t__ mfxStatus ;
struct TYPE_20__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int /*<<< orphan*/  Info; TYPE_2__ member_0; } ;
typedef  TYPE_3__ mfxFrameSurface1 ;
struct TYPE_24__ {scalar_t__* data; } ;
struct TYPE_23__ {TYPE_1__* internal; } ;
struct TYPE_22__ {int session_download_init; scalar_t__ session_download; scalar_t__ child_frames_ref; int /*<<< orphan*/  session_lock; int /*<<< orphan*/  session_cond; } ;
struct TYPE_19__ {TYPE_4__* priv; } ;
typedef  TYPE_4__ QSVFramesContext ;
typedef  TYPE_5__ AVHWFramesContext ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ MFXVideoCORE_SyncOperation (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ MFXVideoVPP_RunFrameVPPAsync (scalar_t__,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ MFX_WRN_DEVICE_BUSY ; 
 scalar_t__ MFX_WRN_IN_EXECUTION ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_usleep (int) ; 
 int /*<<< orphan*/  map_frame_to_surface (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int qsv_init_internal_session (TYPE_5__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int qsv_transfer_data_child (TYPE_5__*,TYPE_6__*,TYPE_6__ const*) ; 

__attribute__((used)) static int qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  const AVFrame *src)
{
    QSVFramesContext  *s = ctx->internal->priv;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = NULL;
    mfxStatus err;
    int ret = 0;

    while (!s->session_download_init && !s->session_download && !ret) {
#if HAVE_PTHREADS
        if (pthread_mutex_trylock(&s->session_lock) == 0) {
#endif
            if (!s->session_download_init) {
                ret = qsv_init_internal_session(ctx, &s->session_download, 0);
                if (s->session_download)
                    s->session_download_init = 1;
            }
#if HAVE_PTHREADS
            pthread_mutex_unlock(&s->session_lock);
            pthread_cond_signal(&s->session_cond);
        } else {
            pthread_mutex_lock(&s->session_lock);
            while (!s->session_download_init && !s->session_download) {
                pthread_cond_wait(&s->session_cond, &s->session_lock);
            }
            pthread_mutex_unlock(&s->session_lock);
        }
#endif
    }

    if (ret < 0)
        return ret;

    if (!s->session_download) {
        if (s->child_frames_ref)
            return qsv_transfer_data_child(ctx, dst, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        return AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst, &out);

    do {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, NULL, &sync);
        if (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } while (err == MFX_WRN_DEVICE_BUSY);

    if (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        return AVERROR_UNKNOWN;
    }

    do {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } while (err == MFX_WRN_IN_EXECUTION);
    if (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        return AVERROR_UNKNOWN;
    }

    return 0;
}