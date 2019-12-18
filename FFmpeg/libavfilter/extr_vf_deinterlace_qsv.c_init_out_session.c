#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_9__ ;
typedef  struct TYPE_52__   TYPE_8__ ;
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_24__ ;
typedef  struct TYPE_44__   TYPE_23__ ;
typedef  struct TYPE_43__   TYPE_22__ ;
typedef  struct TYPE_42__   TYPE_21__ ;
typedef  struct TYPE_41__   TYPE_20__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_19__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  par ;
struct TYPE_53__ {int /*<<< orphan*/  FrameRateExtD; scalar_t__ FrameRateExtN; int /*<<< orphan*/  CropH; int /*<<< orphan*/  CropW; } ;
struct TYPE_30__ {TYPE_9__ Out; TYPE_9__ In; } ;
struct TYPE_38__ {int IOPattern; int AsyncDepth; TYPE_10__ vpp; scalar_t__ NumExtParam; int /*<<< orphan*/ ** ExtParam; } ;
typedef  TYPE_18__ mfxVideoParam ;
typedef  int /*<<< orphan*/  mfxVersion ;
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/  mfxIMPL ;
typedef  int /*<<< orphan*/  mfxHandleType ;
typedef  int /*<<< orphan*/ * mfxHDL ;
struct TYPE_39__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  GetHDL; int /*<<< orphan*/  Unlock; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Alloc; TYPE_24__* pthis; } ;
typedef  TYPE_19__ mfxFrameAllocator ;
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_52__ {int /*<<< orphan*/  den; scalar_t__ num; } ;
struct TYPE_50__ {int /*<<< orphan*/  den; scalar_t__ num; } ;
struct TYPE_49__ {int /*<<< orphan*/  den; scalar_t__ num; } ;
struct TYPE_51__ {TYPE_6__ time_base; TYPE_5__ frame_rate; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_48__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_46__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_40__ {int NumSurface; int Type; TYPE_17__** Surfaces; } ;
struct TYPE_47__ {TYPE_2__ Header; TYPE_1__ In; TYPE_1__ Out; } ;
struct TYPE_45__ {TYPE_12__** outputs; TYPE_7__** inputs; TYPE_20__* priv; } ;
struct TYPE_44__ {TYPE_14__* device_ctx; TYPE_21__* hwctx; } ;
struct TYPE_43__ {int /*<<< orphan*/  session; } ;
struct TYPE_42__ {int frame_type; int nb_surfaces; TYPE_17__* surfaces; } ;
struct TYPE_35__ {int BufferSz; int /*<<< orphan*/  BufferId; } ;
struct TYPE_36__ {int /*<<< orphan*/  Mode; TYPE_15__ Header; } ;
struct TYPE_41__ {int nb_surface_ptrs; int nb_mem_ids; int /*<<< orphan*/  session; scalar_t__ num_ext_buffers; int /*<<< orphan*/ ** ext_buffers; int /*<<< orphan*/ * mem_ids; TYPE_3__ opaque_alloc; TYPE_17__** surface_ptrs; TYPE_16__ deint_conf; int /*<<< orphan*/  mode; TYPE_13__* hw_frames_ctx; } ;
struct TYPE_37__ {TYPE_9__ Info; TYPE_4__ Data; } ;
struct TYPE_34__ {TYPE_22__* hwctx; } ;
struct TYPE_33__ {scalar_t__ data; } ;
struct TYPE_31__ {int /*<<< orphan*/  den; scalar_t__ num; } ;
struct TYPE_32__ {TYPE_11__ time_base; TYPE_8__ frame_rate; } ;
typedef  TYPE_20__ QSVDeintContext ;
typedef  TYPE_21__ AVQSVFramesContext ;
typedef  TYPE_22__ AVQSVDeviceContext ;
typedef  TYPE_23__ AVHWFramesContext ;
typedef  TYPE_24__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 scalar_t__ MFXInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXJoinSession (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MFXQueryIMPL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXQueryVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXVideoCORE_GetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ MFXVideoCORE_SetFrameAllocator (int /*<<< orphan*/ ,TYPE_19__*) ; 
 scalar_t__ MFXVideoCORE_SetHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MFXVideoVPP_Init (int /*<<< orphan*/ ,TYPE_18__*) ; 
 scalar_t__ MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION ; 
 int /*<<< orphan*/  MFX_EXTBUFF_VPP_DEINTERLACING ; 
 int MFX_IOPATTERN_IN_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_IN_VIDEO_MEMORY ; 
 int MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 scalar_t__ QSV_RUNTIME_VERSION_ATLEAST (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_24__*,int /*<<< orphan*/ ,char*,...) ; 
 void* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  frame_alloc ; 
 int /*<<< orphan*/  frame_free ; 
 int /*<<< orphan*/  frame_get_hdl ; 
 int /*<<< orphan*/  frame_lock ; 
 int /*<<< orphan*/  frame_unlock ; 
 int /*<<< orphan*/ * handle_types ; 
 int /*<<< orphan*/  memset (TYPE_18__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_out_session(AVFilterContext *ctx)
{

    QSVDeintContext                  *s = ctx->priv;
    AVHWFramesContext    *hw_frames_ctx = (AVHWFramesContext*)s->hw_frames_ctx->data;
    AVQSVFramesContext *hw_frames_hwctx = hw_frames_ctx->hwctx;
    AVQSVDeviceContext    *device_hwctx = hw_frames_ctx->device_ctx->hwctx;

    int opaque = !!(hw_frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);

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
     * actual deinterlacing */
    err = MFXInit(impl, &ver, &s->session);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a session for deinterlacing\n");
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

    s->deint_conf.Header.BufferId = MFX_EXTBUFF_VPP_DEINTERLACING;
    s->deint_conf.Header.BufferSz = sizeof(s->deint_conf);
    s->deint_conf.Mode = s->mode;

    s->ext_buffers[s->num_ext_buffers++] = (mfxExtBuffer *)&s->deint_conf;

    if (opaque) {
        s->surface_ptrs = av_mallocz_array(hw_frames_hwctx->nb_surfaces,
                                           sizeof(*s->surface_ptrs));
        if (!s->surface_ptrs)
            return AVERROR(ENOMEM);
        for (i = 0; i < hw_frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = hw_frames_hwctx->surfaces + i;
        s->nb_surface_ptrs = hw_frames_hwctx->nb_surfaces;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.NumSurface = s->nb_surface_ptrs;
        s->opaque_alloc.In.Type       = hw_frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = sizeof(s->opaque_alloc);

        s->ext_buffers[s->num_ext_buffers++] = (mfxExtBuffer *)&s->opaque_alloc;

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

        s->mem_ids = av_mallocz_array(hw_frames_hwctx->nb_surfaces,
                                      sizeof(*s->mem_ids));
        if (!s->mem_ids)
            return AVERROR(ENOMEM);
        for (i = 0; i < hw_frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = hw_frames_hwctx->surfaces[i].Data.MemId;
        s->nb_mem_ids = hw_frames_hwctx->nb_surfaces;

        err = MFXVideoCORE_SetFrameAllocator(s->session, &frame_allocator);
        if (err != MFX_ERR_NONE)
            return AVERROR_UNKNOWN;

        par.IOPattern = MFX_IOPATTERN_IN_VIDEO_MEMORY | MFX_IOPATTERN_OUT_VIDEO_MEMORY;
    }

    par.ExtParam    = s->ext_buffers;
    par.NumExtParam = s->num_ext_buffers;

    par.AsyncDepth = 1;    // TODO async

    par.vpp.In = hw_frames_hwctx->surfaces[0].Info;

    par.vpp.In.CropW = ctx->inputs[0]->w;
    par.vpp.In.CropH = ctx->inputs[0]->h;

    if (ctx->inputs[0]->frame_rate.num) {
        par.vpp.In.FrameRateExtN = ctx->inputs[0]->frame_rate.num;
        par.vpp.In.FrameRateExtD = ctx->inputs[0]->frame_rate.den;
    } else {
        par.vpp.In.FrameRateExtN = ctx->inputs[0]->time_base.num;
        par.vpp.In.FrameRateExtD = ctx->inputs[0]->time_base.den;
    }

    par.vpp.Out = par.vpp.In;

    if (ctx->outputs[0]->frame_rate.num) {
        par.vpp.Out.FrameRateExtN = ctx->outputs[0]->frame_rate.num;
        par.vpp.Out.FrameRateExtD = ctx->outputs[0]->frame_rate.den;
    } else {
        par.vpp.Out.FrameRateExtN = ctx->outputs[0]->time_base.num;
        par.vpp.Out.FrameRateExtD = ctx->outputs[0]->time_base.den;
    }

    err = MFXVideoVPP_Init(s->session, &par);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error opening the VPP for deinterlacing: %d\n", err);
        return AVERROR_UNKNOWN;
    }

    return 0;
}