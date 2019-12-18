#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* priv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  camera_mgr; int /*<<< orphan*/  input_queue_size; int /*<<< orphan*/  input_queue; int /*<<< orphan*/  exit; int /*<<< orphan*/  got_image_format; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ACameraManager_create () ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int add_video_stream (TYPE_2__*) ; 
 int /*<<< orphan*/  android_camera_read_close (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_thread_message_queue_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int create_capture_session (TYPE_2__*) ; 
 int create_image_reader (TYPE_2__*) ; 
 int /*<<< orphan*/  get_sensor_orientation (TYPE_2__*) ; 
 int /*<<< orphan*/  match_framerate (TYPE_2__*) ; 
 int /*<<< orphan*/  match_video_size (TYPE_2__*) ; 
 int open_camera (TYPE_2__*) ; 

__attribute__((used)) static int android_camera_read_header(AVFormatContext *avctx)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    int ret;

    atomic_init(&ctx->got_image_format, 0);
    atomic_init(&ctx->exit, 0);

    ret = av_thread_message_queue_alloc(&ctx->input_queue, ctx->input_queue_size, sizeof(AVPacket));
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to allocate input queue, error: %s.\n", av_err2str(ret));
        goto error;
    }

    ctx->camera_mgr = ACameraManager_create();
    if (!ctx->camera_mgr) {
        av_log(avctx, AV_LOG_ERROR, "Failed to create Android camera manager.\n");
        ret = AVERROR_EXTERNAL;
        goto error;
    }

    ret = open_camera(avctx);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to open camera.\n");
        goto error;
    }

    get_sensor_orientation(avctx);
    match_video_size(avctx);
    match_framerate(avctx);

    ret = create_image_reader(avctx);
    if (ret < 0) {
        goto error;
    }

    ret = create_capture_session(avctx);
    if (ret < 0) {
        goto error;
    }

    ret = add_video_stream(avctx);

error:
    if (ret < 0) {
        android_camera_read_close(avctx);
        av_log(avctx, AV_LOG_ERROR, "Failed to open android_camera.\n");
    }

    return ret;
}