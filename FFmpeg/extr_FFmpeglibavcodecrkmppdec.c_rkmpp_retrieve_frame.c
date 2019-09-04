#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_35__ {int nb_planes; TYPE_2__* planes; scalar_t__ format; } ;
struct TYPE_34__ {int interlaced_frame; int top_field_first; void* hw_frames_ctx; int /*<<< orphan*/ * buf; int /*<<< orphan*/ ** data; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_range; int /*<<< orphan*/  pts; void* height; void* width; void* format; } ;
struct TYPE_33__ {void* height; void* width; int /*<<< orphan*/  sw_format; void* format; } ;
struct TYPE_32__ {TYPE_12__* decoder_ref; } ;
struct TYPE_31__ {int eos_reached; TYPE_12__* frames_ref; int /*<<< orphan*/  device_ref; int /*<<< orphan*/  ctx; TYPE_3__* mpi; } ;
struct TYPE_30__ {TYPE_12__* decoder_ref; int /*<<< orphan*/ * frame; } ;
struct TYPE_29__ {int (* decode_get_frame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_28__ {int offset; int pitch; scalar_t__ object_index; } ;
struct TYPE_27__ {int /*<<< orphan*/  size; int /*<<< orphan*/  fd; } ;
struct TYPE_26__ {scalar_t__ data; } ;
struct TYPE_25__ {void* height; void* width; TYPE_6__* priv_data; } ;
struct TYPE_24__ {int nb_objects; int nb_layers; TYPE_9__* layers; TYPE_1__* objects; } ;
typedef  TYPE_4__ RKMPPFrameContext ;
typedef  TYPE_5__ RKMPPDecoder ;
typedef  TYPE_6__ RKMPPDecodeContext ;
typedef  scalar_t__ MppFrameFormat ;
typedef  int /*<<< orphan*/ * MppFrame ;
typedef  int /*<<< orphan*/ * MppBuffer ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  TYPE_8__ AVFrame ;
typedef  TYPE_9__ AVDRMLayerDescriptor ;
typedef  TYPE_10__ AVDRMFrameDescriptor ;
typedef  TYPE_11__ AVCodecContext ;
typedef  TYPE_12__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 void* AV_PIX_FMT_DRM_PRIME ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_PIX_FMT_NV12 ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MPP_DEC_SET_INFO_CHANGE_READY ; 
 int MPP_ERR_TIMEOUT ; 
 int MPP_FRAME_FLAG_DEINTERLACED ; 
 int MPP_FRAME_FLAG_FIELD_ORDER_MASK ; 
 int MPP_FRAME_FLAG_TOP_FIRST ; 
 int MPP_OK ; 
 TYPE_12__* av_buffer_allocz (int) ; 
 int /*<<< orphan*/  av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ) ; 
 void* av_buffer_ref (TYPE_12__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_12__**) ; 
 int /*<<< orphan*/  av_free (TYPE_10__*) ; 
 TYPE_12__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwframe_ctx_init (TYPE_12__*) ; 
 int /*<<< orphan*/  av_log (TYPE_11__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_10__* av_mallocz (int) ; 
 int /*<<< orphan*/  mpp_buffer_get_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_buffer_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_frame_deinit (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * mpp_frame_get_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_frame_get_color_primaries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_frame_get_color_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_frame_get_color_trc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_frame_get_colorspace (int /*<<< orphan*/ *) ; 
 scalar_t__ mpp_frame_get_discard (int /*<<< orphan*/ *) ; 
 scalar_t__ mpp_frame_get_eos (int /*<<< orphan*/ *) ; 
 scalar_t__ mpp_frame_get_errinfo (int /*<<< orphan*/ *) ; 
 scalar_t__ mpp_frame_get_fmt (int /*<<< orphan*/ *) ; 
 void* mpp_frame_get_height (int /*<<< orphan*/ *) ; 
 int mpp_frame_get_hor_stride (int /*<<< orphan*/ *) ; 
 scalar_t__ mpp_frame_get_info_change (int /*<<< orphan*/ *) ; 
 int mpp_frame_get_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpp_frame_get_pts (int /*<<< orphan*/ *) ; 
 int mpp_frame_get_ver_stride (int /*<<< orphan*/ *) ; 
 void* mpp_frame_get_width (int /*<<< orphan*/ *) ; 
 scalar_t__ rkmpp_get_frameformat (scalar_t__) ; 
 int /*<<< orphan*/  rkmpp_release_frame ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rkmpp_retrieve_frame(AVCodecContext *avctx, AVFrame *frame)
{
    RKMPPDecodeContext *rk_context = avctx->priv_data;
    RKMPPDecoder *decoder = (RKMPPDecoder *)rk_context->decoder_ref->data;
    RKMPPFrameContext *framecontext = NULL;
    AVBufferRef *framecontextref = NULL;
    int ret;
    MppFrame mppframe = NULL;
    MppBuffer buffer = NULL;
    AVDRMFrameDescriptor *desc = NULL;
    AVDRMLayerDescriptor *layer = NULL;
    int mode;
    MppFrameFormat mppformat;
    uint32_t drmformat;

    ret = decoder->mpi->decode_get_frame(decoder->ctx, &mppframe);
    if (ret != MPP_OK && ret != MPP_ERR_TIMEOUT) {
        av_log(avctx, AV_LOG_ERROR, "Failed to get a frame from MPP (code = %d)\n", ret);
        goto fail;
    }

    if (mppframe) {
        // Check whether we have a special frame or not
        if (mpp_frame_get_info_change(mppframe)) {
            AVHWFramesContext *hwframes;

            av_log(avctx, AV_LOG_INFO, "Decoder noticed an info change (%dx%d), format=%d\n",
                                        (int)mpp_frame_get_width(mppframe), (int)mpp_frame_get_height(mppframe),
                                        (int)mpp_frame_get_fmt(mppframe));

            avctx->width = mpp_frame_get_width(mppframe);
            avctx->height = mpp_frame_get_height(mppframe);

            decoder->mpi->control(decoder->ctx, MPP_DEC_SET_INFO_CHANGE_READY, NULL);

            av_buffer_unref(&decoder->frames_ref);

            decoder->frames_ref = av_hwframe_ctx_alloc(decoder->device_ref);
            if (!decoder->frames_ref) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            mppformat = mpp_frame_get_fmt(mppframe);
            drmformat = rkmpp_get_frameformat(mppformat);

            hwframes = (AVHWFramesContext*)decoder->frames_ref->data;
            hwframes->format    = AV_PIX_FMT_DRM_PRIME;
            hwframes->sw_format = drmformat == DRM_FORMAT_NV12 ? AV_PIX_FMT_NV12 : AV_PIX_FMT_NONE;
            hwframes->width     = avctx->width;
            hwframes->height    = avctx->height;
            ret = av_hwframe_ctx_init(decoder->frames_ref);
            if (ret < 0)
                goto fail;

            // here decoder is fully initialized, we need to feed it again with data
            ret = AVERROR(EAGAIN);
            goto fail;
        } else if (mpp_frame_get_eos(mppframe)) {
            av_log(avctx, AV_LOG_DEBUG, "Received a EOS frame.\n");
            decoder->eos_reached = 1;
            ret = AVERROR_EOF;
            goto fail;
        } else if (mpp_frame_get_discard(mppframe)) {
            av_log(avctx, AV_LOG_DEBUG, "Received a discard frame.\n");
            ret = AVERROR(EAGAIN);
            goto fail;
        } else if (mpp_frame_get_errinfo(mppframe)) {
            av_log(avctx, AV_LOG_ERROR, "Received a errinfo frame.\n");
            ret = AVERROR_UNKNOWN;
            goto fail;
        }

        // here we should have a valid frame
        av_log(avctx, AV_LOG_DEBUG, "Received a frame.\n");

        // setup general frame fields
        frame->format           = AV_PIX_FMT_DRM_PRIME;
        frame->width            = mpp_frame_get_width(mppframe);
        frame->height           = mpp_frame_get_height(mppframe);
        frame->pts              = mpp_frame_get_pts(mppframe);
        frame->color_range      = mpp_frame_get_color_range(mppframe);
        frame->color_primaries  = mpp_frame_get_color_primaries(mppframe);
        frame->color_trc        = mpp_frame_get_color_trc(mppframe);
        frame->colorspace       = mpp_frame_get_colorspace(mppframe);

        mode = mpp_frame_get_mode(mppframe);
        frame->interlaced_frame = ((mode & MPP_FRAME_FLAG_FIELD_ORDER_MASK) == MPP_FRAME_FLAG_DEINTERLACED);
        frame->top_field_first  = ((mode & MPP_FRAME_FLAG_FIELD_ORDER_MASK) == MPP_FRAME_FLAG_TOP_FIRST);

        mppformat = mpp_frame_get_fmt(mppframe);
        drmformat = rkmpp_get_frameformat(mppformat);

        // now setup the frame buffer info
        buffer = mpp_frame_get_buffer(mppframe);
        if (buffer) {
            desc = av_mallocz(sizeof(AVDRMFrameDescriptor));
            if (!desc) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            desc->nb_objects = 1;
            desc->objects[0].fd = mpp_buffer_get_fd(buffer);
            desc->objects[0].size = mpp_buffer_get_size(buffer);

            desc->nb_layers = 1;
            layer = &desc->layers[0];
            layer->format = drmformat;
            layer->nb_planes = 2;

            layer->planes[0].object_index = 0;
            layer->planes[0].offset = 0;
            layer->planes[0].pitch = mpp_frame_get_hor_stride(mppframe);

            layer->planes[1].object_index = 0;
            layer->planes[1].offset = layer->planes[0].pitch * mpp_frame_get_ver_stride(mppframe);
            layer->planes[1].pitch = layer->planes[0].pitch;

            // we also allocate a struct in buf[0] that will allow to hold additionnal information
            // for releasing properly MPP frames and decoder
            framecontextref = av_buffer_allocz(sizeof(*framecontext));
            if (!framecontextref) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            // MPP decoder needs to be closed only when all frames have been released.
            framecontext = (RKMPPFrameContext *)framecontextref->data;
            framecontext->decoder_ref = av_buffer_ref(rk_context->decoder_ref);
            framecontext->frame = mppframe;

            frame->data[0]  = (uint8_t *)desc;
            frame->buf[0]   = av_buffer_create((uint8_t *)desc, sizeof(*desc), rkmpp_release_frame,
                                               framecontextref, AV_BUFFER_FLAG_READONLY);

            if (!frame->buf[0]) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            frame->hw_frames_ctx = av_buffer_ref(decoder->frames_ref);
            if (!frame->hw_frames_ctx) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            return 0;
        } else {
            av_log(avctx, AV_LOG_ERROR, "Failed to retrieve the frame buffer, frame is dropped (code = %d)\n", ret);
            mpp_frame_deinit(&mppframe);
        }
    } else if (decoder->eos_reached) {
        return AVERROR_EOF;
    } else if (ret == MPP_ERR_TIMEOUT) {
        av_log(avctx, AV_LOG_DEBUG, "Timeout when trying to get a frame from MPP\n");
    }

    return AVERROR(EAGAIN);

fail:
    if (mppframe)
        mpp_frame_deinit(&mppframe);

    if (framecontext)
        av_buffer_unref(&framecontext->decoder_ref);

    if (framecontextref)
        av_buffer_unref(&framecontextref);

    if (desc)
        av_free(desc);

    return ret;
}