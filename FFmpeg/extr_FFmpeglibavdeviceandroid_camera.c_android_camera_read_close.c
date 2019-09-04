#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ input_queue; int /*<<< orphan*/ * camera_mgr; int /*<<< orphan*/  camera_id; int /*<<< orphan*/ * camera_metadata; int /*<<< orphan*/ * image_reader; int /*<<< orphan*/ * camera_dev; int /*<<< orphan*/ * capture_session_output_container; int /*<<< orphan*/ * image_reader_window; int /*<<< orphan*/ * capture_session_output; int /*<<< orphan*/ * camera_output_target; int /*<<< orphan*/ * capture_request; int /*<<< orphan*/ * capture_session; int /*<<< orphan*/  exit; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ACameraCaptureSession_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACameraCaptureSession_stopRepeating (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACameraDevice_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACameraManager_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACameraMetadata_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACameraOutputTarget_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACaptureRequest_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACaptureRequest_removeTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACaptureSessionOutputContainer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACaptureSessionOutputContainer_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACaptureSessionOutput_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AImageReader_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ANativeWindow_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AVERROR_EOF ; 
 int /*<<< orphan*/  AV_THREAD_MESSAGE_NONBLOCK ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_thread_message_queue_free (scalar_t__*) ; 
 scalar_t__ av_thread_message_queue_recv (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_thread_message_queue_set_err_send (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int android_camera_read_close(AVFormatContext *avctx)
{
    AndroidCameraCtx *ctx = avctx->priv_data;

    atomic_store(&ctx->exit, 1);

    if (ctx->capture_session) {
        ACameraCaptureSession_stopRepeating(ctx->capture_session);
        // Following warning is emitted, after capture session closed callback is received:
        // ACameraCaptureSession: Device is closed but session 0 is not notified
        // Seems to be a bug in Android, we can ignore this
        ACameraCaptureSession_close(ctx->capture_session);
        ctx->capture_session = NULL;
    }

    if (ctx->capture_request) {
        ACaptureRequest_removeTarget(ctx->capture_request, ctx->camera_output_target);
        ACaptureRequest_free(ctx->capture_request);
        ctx->capture_request = NULL;
    }

    if (ctx->camera_output_target) {
        ACameraOutputTarget_free(ctx->camera_output_target);
        ctx->camera_output_target = NULL;
    }

    if (ctx->capture_session_output) {
        ACaptureSessionOutputContainer_remove(ctx->capture_session_output_container,
                ctx->capture_session_output);
        ACaptureSessionOutput_free(ctx->capture_session_output);
        ctx->capture_session_output = NULL;
    }

    if (ctx->image_reader_window) {
        ANativeWindow_release(ctx->image_reader_window);
        ctx->image_reader_window = NULL;
    }

    if (ctx->capture_session_output_container) {
        ACaptureSessionOutputContainer_free(ctx->capture_session_output_container);
        ctx->capture_session_output_container = NULL;
    }

    if (ctx->camera_dev) {
        ACameraDevice_close(ctx->camera_dev);
        ctx->camera_dev = NULL;
    }

    if (ctx->image_reader) {
        AImageReader_delete(ctx->image_reader);
        ctx->image_reader = NULL;
    }

    if (ctx->camera_metadata) {
        ACameraMetadata_free(ctx->camera_metadata);
        ctx->camera_metadata = NULL;
    }

    av_freep(&ctx->camera_id);

    if (ctx->camera_mgr) {
        ACameraManager_delete(ctx->camera_mgr);
        ctx->camera_mgr = NULL;
    }

    if (ctx->input_queue) {
        AVPacket pkt;
        av_thread_message_queue_set_err_send(ctx->input_queue, AVERROR_EOF);
        while (av_thread_message_queue_recv(ctx->input_queue, &pkt, AV_THREAD_MESSAGE_NONBLOCK) >= 0) {
            av_packet_unref(&pkt);
        }
        av_thread_message_queue_free(&ctx->input_queue);
    }

    return 0;
}