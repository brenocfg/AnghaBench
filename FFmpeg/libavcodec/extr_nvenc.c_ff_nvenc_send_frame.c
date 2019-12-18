#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  tmp_out_surf ;
typedef  int /*<<< orphan*/  in_surf ;
struct TYPE_40__ {int flags; TYPE_1__* internal; TYPE_4__* priv_data; } ;
struct TYPE_39__ {scalar_t__ pict_type; scalar_t__ pts; scalar_t__ top_field_first; } ;
struct TYPE_38__ {scalar_t__ (* nvEncEncodePicture ) (int /*<<< orphan*/ ,TYPE_6__*) ;} ;
struct TYPE_37__ {scalar_t__ inputTimeStamp; scalar_t__ encodePicFlags; int /*<<< orphan*/  pictureStruct; int /*<<< orphan*/  outputBitstream; int /*<<< orphan*/  inputPitch; int /*<<< orphan*/  inputHeight; int /*<<< orphan*/  inputWidth; int /*<<< orphan*/  bufferFmt; int /*<<< orphan*/  inputBuffer; int /*<<< orphan*/  version; int /*<<< orphan*/  member_0; } ;
struct TYPE_36__ {int payloadType; int /*<<< orphan*/ * payload; scalar_t__ payloadSize; } ;
struct TYPE_34__ {TYPE_7__ nvenc_funcs; } ;
struct TYPE_35__ {int encoder_flushing; scalar_t__* initial_pts; scalar_t__ forced_idr; int /*<<< orphan*/  output_surface_ready_queue; int /*<<< orphan*/  output_surface_queue; int /*<<< orphan*/  timestamp_list; int /*<<< orphan*/  nvencoder; scalar_t__ a53_cc; scalar_t__ first_packet_output; int /*<<< orphan*/  d3d11_device; int /*<<< orphan*/  cu_context; TYPE_3__ nvenc_dload_funcs; } ;
struct TYPE_33__ {int /*<<< orphan*/  output_surface; int /*<<< orphan*/  pitch; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/  input_surface; } ;
struct TYPE_32__ {scalar_t__ draining; } ;
typedef  TYPE_2__ NvencSurface ;
typedef  TYPE_3__ NvencDynLoadFunctions ;
typedef  TYPE_4__ NvencContext ;
typedef  TYPE_5__ NV_ENC_SEI_PAYLOAD ;
typedef  TYPE_6__ NV_ENC_PIC_PARAMS ;
typedef  TYPE_7__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  scalar_t__ NVENCSTATUS ;
typedef  TYPE_8__ AVFrame ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AV_CODEC_FLAG_INTERLACED_DCT ; 
 int /*<<< orphan*/  AV_FRAME_DATA_A53_CC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ NV_ENC_ERR_NEED_MORE_INPUT ; 
 scalar_t__ NV_ENC_PIC_FLAG_EOS ; 
 scalar_t__ NV_ENC_PIC_FLAG_FORCEIDR ; 
 scalar_t__ NV_ENC_PIC_FLAG_FORCEINTRA ; 
 int /*<<< orphan*/  NV_ENC_PIC_PARAMS_VER ; 
 int /*<<< orphan*/  NV_ENC_PIC_STRUCT_FIELD_BOTTOM_TOP ; 
 int /*<<< orphan*/  NV_ENC_PIC_STRUCT_FIELD_TOP_BOTTOM ; 
 int /*<<< orphan*/  NV_ENC_PIC_STRUCT_FRAME ; 
 scalar_t__ NV_ENC_SUCCESS ; 
 int /*<<< orphan*/  av_fifo_generic_read (int /*<<< orphan*/ ,TYPE_2__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,TYPE_2__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_fifo_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ ) ; 
 scalar_t__ av_frame_get_side_data (TYPE_8__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ff_alloc_a53_sei (TYPE_8__ const*,int,void**,size_t*) ; 
 TYPE_2__* get_free_frame (TYPE_4__*) ; 
 int /*<<< orphan*/  nvenc_codec_specific_pic_params (TYPE_9__*,TYPE_6__*,TYPE_5__*) ; 
 int nvenc_pop_context (TYPE_9__*) ; 
 int nvenc_print_error (TYPE_9__*,scalar_t__,char*) ; 
 int nvenc_push_context (TYPE_9__*) ; 
 int nvenc_upload_frame (TYPE_9__*,TYPE_8__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  reconfig_encoder (TYPE_9__*,TYPE_8__ const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  timestamp_queue_enqueue (int /*<<< orphan*/ ,scalar_t__) ; 

int ff_nvenc_send_frame(AVCodecContext *avctx, const AVFrame *frame)
{
    NVENCSTATUS nv_status;
    NvencSurface *tmp_out_surf, *in_surf;
    int res, res2;
    NV_ENC_SEI_PAYLOAD *sei_data = NULL;
    size_t sei_size;

    NvencContext *ctx = avctx->priv_data;
    NvencDynLoadFunctions *dl_fn = &ctx->nvenc_dload_funcs;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &dl_fn->nvenc_funcs;

    NV_ENC_PIC_PARAMS pic_params = { 0 };
    pic_params.version = NV_ENC_PIC_PARAMS_VER;

    if ((!ctx->cu_context && !ctx->d3d11_device) || !ctx->nvencoder)
        return AVERROR(EINVAL);

    if (ctx->encoder_flushing) {
        if (avctx->internal->draining)
            return AVERROR_EOF;

        ctx->encoder_flushing = 0;
        ctx->first_packet_output = 0;
        ctx->initial_pts[0] = AV_NOPTS_VALUE;
        ctx->initial_pts[1] = AV_NOPTS_VALUE;
        av_fifo_reset(ctx->timestamp_list);
    }

    if (frame) {
        in_surf = get_free_frame(ctx);
        if (!in_surf)
            return AVERROR(EAGAIN);

        res = nvenc_push_context(avctx);
        if (res < 0)
            return res;

        reconfig_encoder(avctx, frame);

        res = nvenc_upload_frame(avctx, frame, in_surf);

        res2 = nvenc_pop_context(avctx);
        if (res2 < 0)
            return res2;

        if (res)
            return res;

        pic_params.inputBuffer = in_surf->input_surface;
        pic_params.bufferFmt = in_surf->format;
        pic_params.inputWidth = in_surf->width;
        pic_params.inputHeight = in_surf->height;
        pic_params.inputPitch = in_surf->pitch;
        pic_params.outputBitstream = in_surf->output_surface;

        if (avctx->flags & AV_CODEC_FLAG_INTERLACED_DCT) {
            if (frame->top_field_first)
                pic_params.pictureStruct = NV_ENC_PIC_STRUCT_FIELD_TOP_BOTTOM;
            else
                pic_params.pictureStruct = NV_ENC_PIC_STRUCT_FIELD_BOTTOM_TOP;
        } else {
            pic_params.pictureStruct = NV_ENC_PIC_STRUCT_FRAME;
        }

        if (ctx->forced_idr >= 0 && frame->pict_type == AV_PICTURE_TYPE_I) {
            pic_params.encodePicFlags =
                ctx->forced_idr ? NV_ENC_PIC_FLAG_FORCEIDR : NV_ENC_PIC_FLAG_FORCEINTRA;
        } else {
            pic_params.encodePicFlags = 0;
        }

        pic_params.inputTimeStamp = frame->pts;

        if (ctx->a53_cc && av_frame_get_side_data(frame, AV_FRAME_DATA_A53_CC)) {
            if (ff_alloc_a53_sei(frame, sizeof(NV_ENC_SEI_PAYLOAD), (void**)&sei_data, &sei_size) < 0) {
                av_log(ctx, AV_LOG_ERROR, "Not enough memory for closed captions, skipping\n");
            }

            if (sei_data) {
                sei_data->payloadSize = (uint32_t)sei_size;
                sei_data->payloadType = 4;
                sei_data->payload = (uint8_t*)(sei_data + 1);
            }
        }

        nvenc_codec_specific_pic_params(avctx, &pic_params, sei_data);
    } else {
        pic_params.encodePicFlags = NV_ENC_PIC_FLAG_EOS;
        ctx->encoder_flushing = 1;
    }

    res = nvenc_push_context(avctx);
    if (res < 0)
        return res;

    nv_status = p_nvenc->nvEncEncodePicture(ctx->nvencoder, &pic_params);
    av_free(sei_data);

    res = nvenc_pop_context(avctx);
    if (res < 0)
        return res;

    if (nv_status != NV_ENC_SUCCESS &&
        nv_status != NV_ENC_ERR_NEED_MORE_INPUT)
        return nvenc_print_error(avctx, nv_status, "EncodePicture failed!");

    if (frame) {
        av_fifo_generic_write(ctx->output_surface_queue, &in_surf, sizeof(in_surf), NULL);
        timestamp_queue_enqueue(ctx->timestamp_list, frame->pts);

        if (ctx->initial_pts[0] == AV_NOPTS_VALUE)
            ctx->initial_pts[0] = frame->pts;
        else if (ctx->initial_pts[1] == AV_NOPTS_VALUE)
            ctx->initial_pts[1] = frame->pts;
    }

    /* all the pending buffers are now ready for output */
    if (nv_status == NV_ENC_SUCCESS) {
        while (av_fifo_size(ctx->output_surface_queue) > 0) {
            av_fifo_generic_read(ctx->output_surface_queue, &tmp_out_surf, sizeof(tmp_out_surf), NULL);
            av_fifo_generic_write(ctx->output_surface_ready_queue, &tmp_out_surf, sizeof(tmp_out_surf), NULL);
        }
    }

    return 0;
}