#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  par ;
struct TYPE_25__ {int FrameRateExtN; int FrameRateExtD; } ;
struct TYPE_26__ {TYPE_5__ In; TYPE_5__ Out; } ;
struct TYPE_27__ {int AsyncDepth; TYPE_6__ vpp; int /*<<< orphan*/  IOPattern; int /*<<< orphan*/  NumExtParam; int /*<<< orphan*/  ExtParam; } ;
typedef  TYPE_7__ mfxVideoParam ;
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/ * mfxSession ;
struct TYPE_28__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  GetHDL; int /*<<< orphan*/  Unlock; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Alloc; TYPE_12__* pthis; } ;
typedef  TYPE_8__ mfxFrameAllocator ;
struct TYPE_29__ {int /*<<< orphan*/  ext_buffers; } ;
struct TYPE_24__ {TYPE_5__ Info; } ;
struct TYPE_23__ {TYPE_2__* internal; } ;
struct TYPE_22__ {TYPE_10__* priv; } ;
struct TYPE_21__ {TYPE_9__* priv; } ;
struct TYPE_20__ {TYPE_3__* device_ctx; TYPE_11__* hwctx; TYPE_1__* internal; } ;
struct TYPE_19__ {int frame_type; TYPE_4__* surfaces; } ;
struct TYPE_18__ {scalar_t__ handle; int /*<<< orphan*/  handle_type; int /*<<< orphan*/  ver; int /*<<< orphan*/  impl; } ;
typedef  TYPE_9__ QSVFramesContext ;
typedef  TYPE_10__ QSVDeviceContext ;
typedef  TYPE_11__ AVQSVFramesContext ;
typedef  TYPE_12__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  FF_ARRAY_ELEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFXClose (int /*<<< orphan*/ *) ; 
 scalar_t__ MFXInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ MFXVideoCORE_SetFrameAllocator (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ MFXVideoCORE_SetHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MFXVideoVPP_Init (int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_IOPATTERN_IN_OPAQUE_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_IN_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_IN_VIDEO_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_OUT_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 int /*<<< orphan*/  av_log (TYPE_12__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  frame_alloc ; 
 int /*<<< orphan*/  frame_free ; 
 int /*<<< orphan*/  frame_get_hdl ; 
 int /*<<< orphan*/  frame_lock ; 
 int /*<<< orphan*/  frame_unlock ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, int upload)
{
    QSVFramesContext              *s = ctx->internal->priv;
    AVQSVFramesContext *frames_hwctx = ctx->hwctx;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->internal->priv;
    int opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);

    mfxFrameAllocator frame_allocator = {
        .pthis  = ctx,
        .Alloc  = frame_alloc,
        .Lock   = frame_lock,
        .Unlock = frame_unlock,
        .GetHDL = frame_get_hdl,
        .Free   = frame_free,
    };

    mfxVideoParam par;
    mfxStatus err;

    err = MFXInit(device_priv->impl, &device_priv->ver, session);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an internal session\n");
        return AVERROR_UNKNOWN;
    }

    if (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        if (err != MFX_ERR_NONE)
            return AVERROR_UNKNOWN;
    }

    if (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        if (err != MFX_ERR_NONE)
            return AVERROR_UNKNOWN;
    }

    memset(&par, 0, sizeof(par));

    if (opaque) {
        par.ExtParam    = s->ext_buffers;
        par.NumExtParam = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_OUT_OPAQUE_MEMORY :
                                   MFX_IOPATTERN_IN_OPAQUE_MEMORY;
    } else {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }

    par.IOPattern |= upload ? MFX_IOPATTERN_IN_SYSTEM_MEMORY :
                              MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
    par.AsyncDepth = 1;

    par.vpp.In = frames_hwctx->surfaces[0].Info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.In.FrameRateExtN = 25;
    par.vpp.In.FrameRateExtD = 1;
    par.vpp.Out = par.vpp.In;

    err = MFXVideoVPP_Init(*session, &par);
    if (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");
        MFXClose(*session);
        *session = NULL;
    }

    return 0;
}