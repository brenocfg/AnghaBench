#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxExtBuffer ;
struct TYPE_22__ {int /*<<< orphan*/  CropH; int /*<<< orphan*/  CropW; int /*<<< orphan*/  CropY; int /*<<< orphan*/  CropX; } ;
struct TYPE_21__ {int nb_inputs; int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * inputs; } ;
struct TYPE_17__ {TYPE_8__ Out; TYPE_8__ In; } ;
struct TYPE_16__ {int NumExtParam; int AsyncDepth; int /*<<< orphan*/  IOPattern; int /*<<< orphan*/ ** ExtParam; TYPE_1__ vpp; } ;
struct TYPE_20__ {int nb_ext_buffers; TYPE_15__ vpp_param; int /*<<< orphan*/  session; int /*<<< orphan*/  out_mem_mode; int /*<<< orphan*/  in_mem_mode; int /*<<< orphan*/ ** ext_buffers; int /*<<< orphan*/  opaque_alloc; TYPE_8__* frame_infos; int /*<<< orphan*/  out_sw_format; scalar_t__ filter_frame; } ;
struct TYPE_19__ {size_t in_idx; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_18__ {int num_crop; int num_ext_buf; int /*<<< orphan*/ ** ext_buf; TYPE_3__* crop; int /*<<< orphan*/  out_sw_format; scalar_t__ filter_frame; } ;
typedef  TYPE_2__ QSVVPPParam ;
typedef  TYPE_3__ QSVVPPCrop ;
typedef  TYPE_4__ QSVVPPContext ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ IS_OPAQUE_MEMORY (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SYSTEM_MEMORY (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VIDEO_MEMORY (int /*<<< orphan*/ ) ; 
 int MFXVideoVPP_Init (int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/  MFX_IOPATTERN_IN_OPAQUE_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_IN_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_IN_VIDEO_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_OUT_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_4__* av_mallocz (int) ; 
 void* av_mallocz_array (int,int) ; 
 scalar_t__ ff_filter_frame ; 
 int /*<<< orphan*/  ff_qsvvpp_free (TYPE_4__**) ; 
 int fill_frameinfo_by_link (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int init_vpp_session (TYPE_5__*,TYPE_4__*) ; 

int ff_qsvvpp_create(AVFilterContext *avctx, QSVVPPContext **vpp, QSVVPPParam *param)
{
    int i;
    int ret;
    QSVVPPContext *s;

    s = av_mallocz(sizeof(*s));
    if (!s)
        return AVERROR(ENOMEM);

    s->filter_frame  = param->filter_frame;
    if (!s->filter_frame)
        s->filter_frame = ff_filter_frame;
    s->out_sw_format = param->out_sw_format;

    /* create the vpp session */
    ret = init_vpp_session(avctx, s);
    if (ret < 0)
        goto failed;

    s->frame_infos = av_mallocz_array(avctx->nb_inputs, sizeof(*s->frame_infos));
    if (!s->frame_infos) {
        ret = AVERROR(ENOMEM);
        goto failed;
    }

    /* Init each input's information */
    for (i = 0; i < avctx->nb_inputs; i++) {
        ret = fill_frameinfo_by_link(&s->frame_infos[i], avctx->inputs[i]);
        if (ret < 0)
            goto failed;
    }

    /* Update input's frame info according to crop */
    for (i = 0; i < param->num_crop; i++) {
        QSVVPPCrop *crop = param->crop + i;
        if (crop->in_idx > avctx->nb_inputs) {
            ret = AVERROR(EINVAL);
            goto failed;
        }
        s->frame_infos[crop->in_idx].CropX = crop->x;
        s->frame_infos[crop->in_idx].CropY = crop->y;
        s->frame_infos[crop->in_idx].CropW = crop->w;
        s->frame_infos[crop->in_idx].CropH = crop->h;
    }

    s->vpp_param.vpp.In = s->frame_infos[0];

    ret = fill_frameinfo_by_link(&s->vpp_param.vpp.Out, avctx->outputs[0]);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Fail to get frame info from link.\n");
        goto failed;
    }

    if (IS_OPAQUE_MEMORY(s->in_mem_mode) || IS_OPAQUE_MEMORY(s->out_mem_mode)) {
        s->nb_ext_buffers = param->num_ext_buf + 1;
        s->ext_buffers = av_mallocz_array(s->nb_ext_buffers, sizeof(*s->ext_buffers));
        if (!s->ext_buffers) {
            ret = AVERROR(ENOMEM);
            goto failed;
        }

        s->ext_buffers[0] = (mfxExtBuffer *)&s->opaque_alloc;
        for (i = 1; i < param->num_ext_buf; i++)
            s->ext_buffers[i]    = param->ext_buf[i - 1];
        s->vpp_param.ExtParam    = s->ext_buffers;
        s->vpp_param.NumExtParam = s->nb_ext_buffers;
    } else {
        s->vpp_param.NumExtParam = param->num_ext_buf;
        s->vpp_param.ExtParam    = param->ext_buf;
    }

    s->vpp_param.AsyncDepth = 1;

    if (IS_SYSTEM_MEMORY(s->in_mem_mode))
        s->vpp_param.IOPattern |= MFX_IOPATTERN_IN_SYSTEM_MEMORY;
    else if (IS_VIDEO_MEMORY(s->in_mem_mode))
        s->vpp_param.IOPattern |= MFX_IOPATTERN_IN_VIDEO_MEMORY;
    else if (IS_OPAQUE_MEMORY(s->in_mem_mode))
        s->vpp_param.IOPattern |= MFX_IOPATTERN_IN_OPAQUE_MEMORY;

    if (IS_SYSTEM_MEMORY(s->out_mem_mode))
        s->vpp_param.IOPattern |= MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
    else if (IS_VIDEO_MEMORY(s->out_mem_mode))
        s->vpp_param.IOPattern |= MFX_IOPATTERN_OUT_VIDEO_MEMORY;
    else if (IS_OPAQUE_MEMORY(s->out_mem_mode))
        s->vpp_param.IOPattern |= MFX_IOPATTERN_OUT_OPAQUE_MEMORY;

    ret = MFXVideoVPP_Init(s->session, &s->vpp_param);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to create a qsvvpp, ret = %d.\n", ret);
        goto failed;
    }

    *vpp = s;
    return 0;

failed:
    ff_qsvvpp_free(&s);

    return ret;
}