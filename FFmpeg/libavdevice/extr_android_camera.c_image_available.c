#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ media_status_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_11__ {TYPE_1__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  pts; int /*<<< orphan*/  stream_index; } ;
struct TYPE_9__ {int image_format; int /*<<< orphan*/  input_queue_size; int /*<<< orphan*/  exit; int /*<<< orphan*/  input_queue; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  got_image_format; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AImageReader ;
typedef  int /*<<< orphan*/  AImage ;

/* Variables and functions */
 scalar_t__ AImageReader_acquireLatestImage (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AImage_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AImage_getPlaneData (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  AImage_getPlaneRowStride (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AImage_getTimestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AMEDIA_IMGREADER_NO_BUFFER_AVAILABLE ; 
 scalar_t__ AMEDIA_OK ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  AV_PIX_FMT_NV12 130 
#define  AV_PIX_FMT_NV21 129 
#define  AV_PIX_FMT_YUV420P 128 
 int /*<<< orphan*/  AV_THREAD_MESSAGE_NONBLOCK ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  VIDEO_STREAM_INDEX ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_image_copy_to_buffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int av_image_get_buffer_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int av_thread_message_queue_send (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_thread_message_queue_set_err_recv (int /*<<< orphan*/ ,int) ; 
 int get_image_format (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_status_string (scalar_t__) ; 

__attribute__((used)) static void image_available(void *context, AImageReader *reader)
{
    AVFormatContext *avctx = context;
    AndroidCameraCtx *ctx = avctx->priv_data;
    media_status_t media_status;
    int ret = 0;

    AImage *image;
    int64_t image_timestamp;
    int32_t image_linestrides[4];
    uint8_t *image_plane_data[4];
    int plane_data_length[4];

    AVPacket pkt;
    int pkt_buffer_size = 0;

    media_status = AImageReader_acquireLatestImage(reader, &image);
    if (media_status != AMEDIA_OK) {
        if (media_status == AMEDIA_IMGREADER_NO_BUFFER_AVAILABLE) {
            av_log(avctx, AV_LOG_WARNING,
                   "An image reader frame was discarded");
        } else {
            av_log(avctx, AV_LOG_ERROR,
                   "Failed to acquire latest image from image reader, error: %s.\n",
                   media_status_string(media_status));
            ret = AVERROR_EXTERNAL;
        }
        goto error;
    }

    // Silently drop frames when exit is set
    if (atomic_load(&ctx->exit)) {
        goto error;
    }

    // Determine actual image format
    if (!atomic_load(&ctx->got_image_format)) {
        ret = get_image_format(avctx, image);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Could not get image format of camera.\n");
            goto error;
        } else {
            atomic_store(&ctx->got_image_format, 1);
        }
    }

    pkt_buffer_size = av_image_get_buffer_size(ctx->image_format, ctx->width, ctx->height, 32);
    AImage_getTimestamp(image, &image_timestamp);

    AImage_getPlaneRowStride(image, 0, &image_linestrides[0]);
    AImage_getPlaneData(image, 0, &image_plane_data[0], &plane_data_length[0]);

    switch (ctx->image_format) {
        case AV_PIX_FMT_YUV420P:
            AImage_getPlaneRowStride(image, 1, &image_linestrides[1]);
            AImage_getPlaneData(image, 1, &image_plane_data[1], &plane_data_length[1]);
            AImage_getPlaneRowStride(image, 2, &image_linestrides[2]);
            AImage_getPlaneData(image, 2, &image_plane_data[2], &plane_data_length[2]);
            break;
        case AV_PIX_FMT_NV12:
            AImage_getPlaneRowStride(image, 1, &image_linestrides[1]);
            AImage_getPlaneData(image, 1, &image_plane_data[1], &plane_data_length[1]);
            break;
        case AV_PIX_FMT_NV21:
            AImage_getPlaneRowStride(image, 2, &image_linestrides[1]);
            AImage_getPlaneData(image, 2, &image_plane_data[1], &plane_data_length[1]);
            break;
        default:
            av_log(avctx, AV_LOG_ERROR, "Unsupported camera image format.\n");
            ret = AVERROR(ENOSYS);
            goto error;
    }

    ret = av_new_packet(&pkt, pkt_buffer_size);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to create new av packet, error: %s.\n", av_err2str(ret));
        goto error;
    }

    pkt.stream_index = VIDEO_STREAM_INDEX;
    pkt.pts = image_timestamp;
    av_image_copy_to_buffer(pkt.data, pkt_buffer_size,
                            (const uint8_t * const *) image_plane_data,
                            image_linestrides, ctx->image_format,
                            ctx->width, ctx->height, 32);

    ret = av_thread_message_queue_send(ctx->input_queue, &pkt, AV_THREAD_MESSAGE_NONBLOCK);

error:
    if (ret < 0) {
        if (ret != AVERROR(EAGAIN)) {
            av_log(avctx, AV_LOG_ERROR,
                   "Error while processing new image, error: %s.\n", av_err2str(ret));
            av_thread_message_queue_set_err_recv(ctx->input_queue, ret);
            atomic_store(&ctx->exit, 1);
        } else {
            av_log(avctx, AV_LOG_WARNING,
                   "Input queue was full, dropping frame, consider raising the input_queue_size option (current value: %d)\n",
                   ctx->input_queue_size);
        }
        if (pkt_buffer_size) {
            av_packet_unref(&pkt);
        }
    }

    AImage_delete(image);

    return;
}