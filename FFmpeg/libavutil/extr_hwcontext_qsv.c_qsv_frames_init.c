#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_21__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  sw_format; TYPE_8__* hwctx; TYPE_1__* internal; } ;
struct TYPE_20__ {int frame_type; int nb_surfaces; TYPE_6__* surfaces; } ;
struct TYPE_15__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_14__ {int NumSurface; int Type; TYPE_6__** Surfaces; } ;
struct TYPE_16__ {TYPE_3__ Header; TYPE_2__ In; TYPE_2__ Out; } ;
struct TYPE_19__ {int /*<<< orphan*/  session_cond; int /*<<< orphan*/  session_lock; scalar_t__ session_upload_init; scalar_t__ session_download_init; int /*<<< orphan*/ * session_upload; int /*<<< orphan*/ * session_download; int /*<<< orphan*/ * mem_ids; TYPE_4__ opaque_alloc; int /*<<< orphan*/ ** ext_buffers; TYPE_6__** surface_ptrs; } ;
struct TYPE_17__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_18__ {TYPE_5__ Data; } ;
struct TYPE_13__ {TYPE_7__* priv; } ;
typedef  TYPE_7__ QSVFramesContext ;
typedef  TYPE_8__ AVQSVFramesContext ;
typedef  TYPE_9__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 void* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsv_fourcc_from_pix_fmt (int /*<<< orphan*/ ) ; 
 int qsv_init_pool (TYPE_9__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->internal->priv;
    AVQSVFramesContext *frames_hwctx = ctx->hwctx;

    int opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);

    uint32_t fourcc;
    int i, ret;

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    if (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        return AVERROR(ENOSYS);
    }

    if (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            return ret;
        }
    }

    if (opaque) {
        s->surface_ptrs = av_mallocz_array(frames_hwctx->nb_surfaces,
                                           sizeof(*s->surface_ptrs));
        if (!s->surface_ptrs)
            return AVERROR(ENOMEM);

        for (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.NumSurface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = sizeof(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    } else {
        s->mem_ids = av_mallocz_array(frames_hwctx->nb_surfaces, sizeof(*s->mem_ids));
        if (!s->mem_ids)
            return AVERROR(ENOMEM);

        for (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }

    s->session_download = NULL;
    s->session_upload   = NULL;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#if HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, NULL);
    pthread_cond_init(&s->session_cond, NULL);
#endif

    return 0;
}