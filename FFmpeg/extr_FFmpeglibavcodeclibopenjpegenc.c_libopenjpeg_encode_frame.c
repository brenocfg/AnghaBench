#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_stream_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
typedef  int /*<<< orphan*/  opj_codec_t ;
struct TYPE_35__ {int pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_34__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_33__ {int /*<<< orphan*/  flags; } ;
struct TYPE_32__ {int /*<<< orphan*/  enc_params; int /*<<< orphan*/  format; } ;
struct TYPE_31__ {int /*<<< orphan*/  pos; TYPE_3__* packet; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PacketWriter ;
typedef  TYPE_2__ LibOpenJPEGContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ const AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_GBR24P 178 
#define  AV_PIX_FMT_GBRP10 177 
#define  AV_PIX_FMT_GBRP12 176 
#define  AV_PIX_FMT_GBRP14 175 
#define  AV_PIX_FMT_GBRP16 174 
#define  AV_PIX_FMT_GBRP9 173 
#define  AV_PIX_FMT_GRAY10 172 
#define  AV_PIX_FMT_GRAY12 171 
#define  AV_PIX_FMT_GRAY14 170 
#define  AV_PIX_FMT_GRAY16 169 
#define  AV_PIX_FMT_GRAY8 168 
#define  AV_PIX_FMT_RGB24 167 
#define  AV_PIX_FMT_RGB48 166 
#define  AV_PIX_FMT_RGBA 165 
#define  AV_PIX_FMT_RGBA64 164 
#define  AV_PIX_FMT_XYZ12 163 
#define  AV_PIX_FMT_YA16 162 
#define  AV_PIX_FMT_YA8 161 
#define  AV_PIX_FMT_YUV410P 160 
#define  AV_PIX_FMT_YUV411P 159 
#define  AV_PIX_FMT_YUV420P 158 
#define  AV_PIX_FMT_YUV420P10 157 
#define  AV_PIX_FMT_YUV420P12 156 
#define  AV_PIX_FMT_YUV420P14 155 
#define  AV_PIX_FMT_YUV420P16 154 
#define  AV_PIX_FMT_YUV420P9 153 
#define  AV_PIX_FMT_YUV422P 152 
#define  AV_PIX_FMT_YUV422P10 151 
#define  AV_PIX_FMT_YUV422P12 150 
#define  AV_PIX_FMT_YUV422P14 149 
#define  AV_PIX_FMT_YUV422P16 148 
#define  AV_PIX_FMT_YUV422P9 147 
#define  AV_PIX_FMT_YUV440P 146 
#define  AV_PIX_FMT_YUV444P 145 
#define  AV_PIX_FMT_YUV444P10 144 
#define  AV_PIX_FMT_YUV444P12 143 
#define  AV_PIX_FMT_YUV444P14 142 
#define  AV_PIX_FMT_YUV444P16 141 
#define  AV_PIX_FMT_YUV444P9 140 
#define  AV_PIX_FMT_YUVA420P 139 
#define  AV_PIX_FMT_YUVA420P10 138 
#define  AV_PIX_FMT_YUVA420P16 137 
#define  AV_PIX_FMT_YUVA420P9 136 
#define  AV_PIX_FMT_YUVA422P 135 
#define  AV_PIX_FMT_YUVA422P10 134 
#define  AV_PIX_FMT_YUVA422P16 133 
#define  AV_PIX_FMT_YUVA422P9 132 
#define  AV_PIX_FMT_YUVA444P 131 
#define  AV_PIX_FMT_YUVA444P10 130 
#define  AV_PIX_FMT_YUVA444P16 129 
#define  AV_PIX_FMT_YUVA444P9 128 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  OPJ_STREAM_WRITE ; 
 TYPE_4__ const* av_frame_clone (TYPE_4__ const*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__ const**) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int const) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_callback ; 
 int ff_alloc_packet2 (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_callback ; 
 int libopenjpeg_copy_packed12 (TYPE_5__*,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int libopenjpeg_copy_packed16 (TYPE_5__*,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int libopenjpeg_copy_packed8 (TYPE_5__*,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int libopenjpeg_copy_unpacked16 (TYPE_5__*,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int libopenjpeg_copy_unpacked8 (TYPE_5__*,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mj2_create_image (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opj_create_compress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_destroy_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_encode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_end_compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_image_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_set_error_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  opj_set_info_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  opj_set_warning_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  opj_setup_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_start_compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opj_stream_default_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_stream_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_set_seek_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_stream_set_skip_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_stream_set_user_data (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_stream_set_write_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_seek ; 
 int /*<<< orphan*/  stream_skip ; 
 int /*<<< orphan*/  stream_write ; 
 int /*<<< orphan*/  warning_callback ; 

__attribute__((used)) static int libopenjpeg_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                    const AVFrame *frame, int *got_packet)
{
    LibOpenJPEGContext *ctx = avctx->priv_data;
    int ret;
    AVFrame *gbrframe;
    int cpyresult = 0;
    PacketWriter writer     = { 0 };
    opj_codec_t *compress   = NULL;
    opj_stream_t *stream    = NULL;
    opj_image_t *image      = mj2_create_image(avctx, &ctx->enc_params);
    if (!image) {
        av_log(avctx, AV_LOG_ERROR, "Error creating the mj2 image\n");
        ret = AVERROR(EINVAL);
        goto done;
    }

    switch (avctx->pix_fmt) {
    case AV_PIX_FMT_RGB24:
    case AV_PIX_FMT_RGBA:
    case AV_PIX_FMT_YA8:
        cpyresult = libopenjpeg_copy_packed8(avctx, frame, image);
        break;
    case AV_PIX_FMT_XYZ12:
        cpyresult = libopenjpeg_copy_packed12(avctx, frame, image);
        break;
    case AV_PIX_FMT_RGB48:
    case AV_PIX_FMT_RGBA64:
    case AV_PIX_FMT_YA16:
        cpyresult = libopenjpeg_copy_packed16(avctx, frame, image);
        break;
    case AV_PIX_FMT_GBR24P:
    case AV_PIX_FMT_GBRP9:
    case AV_PIX_FMT_GBRP10:
    case AV_PIX_FMT_GBRP12:
    case AV_PIX_FMT_GBRP14:
    case AV_PIX_FMT_GBRP16:
        gbrframe = av_frame_clone(frame);
        if (!gbrframe) {
            ret = AVERROR(ENOMEM);
            goto done;
        }
        gbrframe->data[0] = frame->data[2]; // swap to be rgb
        gbrframe->data[1] = frame->data[0];
        gbrframe->data[2] = frame->data[1];
        gbrframe->linesize[0] = frame->linesize[2];
        gbrframe->linesize[1] = frame->linesize[0];
        gbrframe->linesize[2] = frame->linesize[1];
        if (avctx->pix_fmt == AV_PIX_FMT_GBR24P) {
            cpyresult = libopenjpeg_copy_unpacked8(avctx, gbrframe, image);
        } else {
            cpyresult = libopenjpeg_copy_unpacked16(avctx, gbrframe, image);
        }
        av_frame_free(&gbrframe);
        break;
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_YUV410P:
    case AV_PIX_FMT_YUV411P:
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUV440P:
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUVA420P:
    case AV_PIX_FMT_YUVA422P:
    case AV_PIX_FMT_YUVA444P:
        cpyresult = libopenjpeg_copy_unpacked8(avctx, frame, image);
        break;
    case AV_PIX_FMT_GRAY10:
    case AV_PIX_FMT_GRAY12:
    case AV_PIX_FMT_GRAY14:
    case AV_PIX_FMT_GRAY16:
    case AV_PIX_FMT_YUV420P9:
    case AV_PIX_FMT_YUV422P9:
    case AV_PIX_FMT_YUV444P9:
    case AV_PIX_FMT_YUVA420P9:
    case AV_PIX_FMT_YUVA422P9:
    case AV_PIX_FMT_YUVA444P9:
    case AV_PIX_FMT_YUV444P10:
    case AV_PIX_FMT_YUV422P10:
    case AV_PIX_FMT_YUV420P10:
    case AV_PIX_FMT_YUVA444P10:
    case AV_PIX_FMT_YUVA422P10:
    case AV_PIX_FMT_YUVA420P10:
    case AV_PIX_FMT_YUV420P12:
    case AV_PIX_FMT_YUV422P12:
    case AV_PIX_FMT_YUV444P12:
    case AV_PIX_FMT_YUV420P14:
    case AV_PIX_FMT_YUV422P14:
    case AV_PIX_FMT_YUV444P14:
    case AV_PIX_FMT_YUV444P16:
    case AV_PIX_FMT_YUV422P16:
    case AV_PIX_FMT_YUV420P16:
    case AV_PIX_FMT_YUVA444P16:
    case AV_PIX_FMT_YUVA422P16:
    case AV_PIX_FMT_YUVA420P16:
        cpyresult = libopenjpeg_copy_unpacked16(avctx, frame, image);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR,
               "The frame's pixel format '%s' is not supported\n",
               av_get_pix_fmt_name(avctx->pix_fmt));
        ret = AVERROR(EINVAL);
        goto done;
        break;
    }

    if (!cpyresult) {
        av_log(avctx, AV_LOG_ERROR,
               "Could not copy the frame data to the internal image buffer\n");
        ret = -1;
        goto done;
    }

    if ((ret = ff_alloc_packet2(avctx, pkt, 1024, 0)) < 0) {
        goto done;
    }

    compress = opj_create_compress(ctx->format);
    if (!compress) {
        av_log(avctx, AV_LOG_ERROR, "Error creating the compressor\n");
        ret = AVERROR(ENOMEM);
        goto done;
    }

    if (!opj_set_error_handler(compress, error_callback, avctx) ||
        !opj_set_warning_handler(compress, warning_callback, avctx) ||
        !opj_set_info_handler(compress, info_callback, avctx)) {
        av_log(avctx, AV_LOG_ERROR, "Error setting the compressor handlers\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    if (!opj_setup_encoder(compress, &ctx->enc_params, image)) {
        av_log(avctx, AV_LOG_ERROR, "Error setting up the compressor\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }
    stream = opj_stream_default_create(OPJ_STREAM_WRITE);

    if (!stream) {
        av_log(avctx, AV_LOG_ERROR, "Error creating the cio stream\n");
        ret = AVERROR(ENOMEM);
        goto done;
    }

    writer.packet = pkt;
    opj_stream_set_write_function(stream, stream_write);
    opj_stream_set_skip_function(stream, stream_skip);
    opj_stream_set_seek_function(stream, stream_seek);
    opj_stream_set_user_data(stream, &writer, NULL);

    if (!opj_start_compress(compress, image, stream) ||
        !opj_encode(compress, stream) ||
        !opj_end_compress(compress, stream)) {
        av_log(avctx, AV_LOG_ERROR, "Error during the opj encode\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    av_shrink_packet(pkt, writer.pos);

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    ret = 0;

done:
    opj_stream_destroy(stream);
    opj_destroy_codec(compress);
    opj_image_destroy(image);
    return ret;
}