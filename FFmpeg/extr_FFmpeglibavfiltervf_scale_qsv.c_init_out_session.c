#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  par ;
struct TYPE_40__ {int FrameRateExtN; int FrameRateExtD; } ;
struct TYPE_41__ {TYPE_4__ Out; TYPE_4__ In; } ;
struct TYPE_30__ {int NumExtParam; int IOPattern; int AsyncDepth; TYPE_5__ vpp; int /*<<< orphan*/ ** ExtParam; } ;
typedef  TYPE_14__ mfxVideoParam ;
typedef  int /*<<< orphan*/  mfxVersion ;
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/  mfxIMPL ;
typedef  int /*<<< orphan*/ * mfxHandleType ;
typedef  int /*<<< orphan*/ * mfxHDL ;
struct TYPE_31__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  GetHDL; int /*<<< orphan*/  Unlock; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Alloc; TYPE_20__* pthis; } ;
typedef  TYPE_15__ mfxFrameAllocator ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_45__ {TYPE_8__* hw_frames_ctx; } ;
struct TYPE_44__ {scalar_t__ data; } ;
struct TYPE_43__ {TYPE_6__* hw_frames_ctx; } ;
struct TYPE_42__ {scalar_t__ data; } ;
struct TYPE_39__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_38__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_37__ {TYPE_9__** outputs; TYPE_7__** inputs; TYPE_16__* priv; } ;
struct TYPE_36__ {int NumSurface; int Type; TYPE_12__** Surfaces; } ;
struct TYPE_35__ {TYPE_10__* device_ctx; TYPE_17__* hwctx; } ;
struct TYPE_34__ {int /*<<< orphan*/  session; } ;
struct TYPE_33__ {int frame_type; int nb_surfaces; TYPE_12__* surfaces; } ;
struct TYPE_27__ {int NumSurface; int Type; TYPE_12__** Surfaces; } ;
struct TYPE_29__ {TYPE_2__ Header; TYPE_1__ Out; TYPE_11__ In; } ;
struct TYPE_32__ {int nb_surface_ptrs_in; int nb_surface_ptrs_out; int nb_mem_ids_in; int nb_mem_ids_out; int /*<<< orphan*/  session; int /*<<< orphan*/ * mem_ids_out; int /*<<< orphan*/ * mem_ids_in; int /*<<< orphan*/ ** ext_buffers; TYPE_13__ opaque_alloc; TYPE_12__** surface_ptrs_out; TYPE_12__** surface_ptrs_in; } ;
struct TYPE_28__ {TYPE_4__ Info; TYPE_3__ Data; } ;
struct TYPE_26__ {TYPE_18__* hwctx; } ;
typedef  TYPE_16__ QSVScaleContext ;
typedef  TYPE_17__ AVQSVFramesContext ;
typedef  TYPE_18__ AVQSVDeviceContext ;
typedef  TYPE_19__ AVHWFramesContext ;
typedef  TYPE_20__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ **) ; 
 scalar_t__ MFXInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXJoinSession (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MFXQueryIMPL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXQueryVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXVideoCORE_GetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ MFXVideoCORE_SetFrameAllocator (int /*<<< orphan*/ ,TYPE_15__*) ; 
 scalar_t__ MFXVideoCORE_SetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXVideoVPP_Init (int /*<<< orphan*/ ,TYPE_14__*) ; 
 scalar_t__ MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION ; 
 int MFX_IOPATTERN_IN_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_IN_VIDEO_MEMORY ; 
 int MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 scalar_t__ QSV_RUNTIME_VERSION_ATLEAST (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_20__*,int /*<<< orphan*/ ,char*) ; 
 void* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  frame_alloc ; 
 int /*<<< orphan*/  frame_free ; 
 int /*<<< orphan*/  frame_get_hdl ; 
 int /*<<< orphan*/  frame_lock ; 
 int /*<<< orphan*/  frame_unlock ; 
 int /*<<< orphan*/ ** handle_types ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_out_session(AVFilterContext *ctx)
{

    QSVScaleContext                   *s = ctx->priv;
    AVHWFramesContext     *in_frames_ctx = (AVHWFramesContext*)ctx->inputs[0]->hw_frames_ctx->data;
    AVHWFramesContext    *out_frames_ctx = (AVHWFramesContext*)ctx->outputs[0]->hw_frames_ctx->data;
    AVQSVFramesContext  *in_frames_hwctx = in_frames_ctx->hwctx;
    AVQSVFramesContext *out_frames_hwctx = out_frames_ctx->hwctx;
    AVQSVDeviceContext     *device_hwctx = in_frames_ctx->device_ctx->hwctx;

    int opaque = !!(in_frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);

    mfxHDL handle = NULL;
    mfxHandleType handle_type;
    mfxVersion ver;
    mfxIMPL impl;
    mfxVideoParam par;
    mfxStatus err;
    int i;

    /* extract the properties of the "master" session given to us */
    err = MFXQueryIMPL(device_hwctx->session, &impl);
    if (err == MFX_ERR_NONE)
        err = MFXQueryVersion(device_hwctx->session, &ver);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        return AVERROR_UNKNOWN;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(handle_types); i++) {
        err = MFXVideoCORE_GetHandle(device_hwctx->session, handle_types[i], &handle);
        if (err == MFX_ERR_NONE) {
            handle_type = handle_types[i];
            break;
        }
    }

    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error getting the session handle\n");
        return AVERROR_UNKNOWN;
    }

    /* create a "slave" session with those same properties, to be used for
     * actual scaling */
    err = MFXInit(impl, &ver, &s->session);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a session for scaling\n");
        return AVERROR_UNKNOWN;
    }

    if (handle) {
        err = MFXVideoCORE_SetHandle(s->session, handle_type, handle);
        if (err != MFX_ERR_NONE)
            return AVERROR_UNKNOWN;
    }

    if (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(device_hwctx->session, s->session);
            if (err != MFX_ERR_NONE)
                return AVERROR_UNKNOWN;
    }

    memset(&par, 0, sizeof(par));

    if (opaque) {
        s->surface_ptrs_in = av_mallocz_array(in_frames_hwctx->nb_surfaces,
                                              sizeof(*s->surface_ptrs_in));
        if (!s->surface_ptrs_in)
            return AVERROR(ENOMEM);
        for (i = 0; i < in_frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs_in[i] = in_frames_hwctx->surfaces + i;
        s->nb_surface_ptrs_in = in_frames_hwctx->nb_surfaces;

        s->surface_ptrs_out = av_mallocz_array(out_frames_hwctx->nb_surfaces,
                                               sizeof(*s->surface_ptrs_out));
        if (!s->surface_ptrs_out)
            return AVERROR(ENOMEM);
        for (i = 0; i < out_frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs_out[i] = out_frames_hwctx->surfaces + i;
        s->nb_surface_ptrs_out = out_frames_hwctx->nb_surfaces;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs_in;
        s->opaque_alloc.In.NumSurface = s->nb_surface_ptrs_in;
        s->opaque_alloc.In.Type       = in_frames_hwctx->frame_type;

        s->opaque_alloc.Out.Surfaces   = s->surface_ptrs_out;
        s->opaque_alloc.Out.NumSurface = s->nb_surface_ptrs_out;
        s->opaque_alloc.Out.Type       = out_frames_hwctx->frame_type;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = sizeof(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;

        par.ExtParam    = s->ext_buffers;
        par.NumExtParam = FF_ARRAY_ELEMS(s->ext_buffers);

        par.IOPattern = MFX_IOPATTERN_IN_OPAQUE_MEMORY | MFX_IOPATTERN_OUT_OPAQUE_MEMORY;
    } else {
        mfxFrameAllocator frame_allocator = {
            .pthis  = ctx,
            .Alloc  = frame_alloc,
            .Lock   = frame_lock,
            .Unlock = frame_unlock,
            .GetHDL = frame_get_hdl,
            .Free   = frame_free,
        };

        s->mem_ids_in = av_mallocz_array(in_frames_hwctx->nb_surfaces,
                                         sizeof(*s->mem_ids_in));
        if (!s->mem_ids_in)
            return AVERROR(ENOMEM);
        for (i = 0; i < in_frames_hwctx->nb_surfaces; i++)
            s->mem_ids_in[i] = in_frames_hwctx->surfaces[i].Data.MemId;
        s->nb_mem_ids_in = in_frames_hwctx->nb_surfaces;

        s->mem_ids_out = av_mallocz_array(out_frames_hwctx->nb_surfaces,
                                          sizeof(*s->mem_ids_out));
        if (!s->mem_ids_out)
            return AVERROR(ENOMEM);
        for (i = 0; i < out_frames_hwctx->nb_surfaces; i++)
            s->mem_ids_out[i] = out_frames_hwctx->surfaces[i].Data.MemId;
        s->nb_mem_ids_out = out_frames_hwctx->nb_surfaces;

        err = MFXVideoCORE_SetFrameAllocator(s->session, &frame_allocator);
        if (err != MFX_ERR_NONE)
            return AVERROR_UNKNOWN;

        par.IOPattern = MFX_IOPATTERN_IN_VIDEO_MEMORY | MFX_IOPATTERN_OUT_VIDEO_MEMORY;
    }

    par.AsyncDepth = 1;    // TODO async

    par.vpp.In  = in_frames_hwctx->surfaces[0].Info;
    par.vpp.Out = out_frames_hwctx->surfaces[0].Info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing scaling here, we just invent an arbitrary
     * value */
    par.vpp.In.FrameRateExtN  = 25;
    par.vpp.In.FrameRateExtD  = 1;
    par.vpp.Out.FrameRateExtN = 25;
    par.vpp.Out.FrameRateExtD = 1;

    err = MFXVideoVPP_Init(s->session, &par);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error opening the VPP for scaling\n");
        return AVERROR_UNKNOWN;
    }

    return 0;
}