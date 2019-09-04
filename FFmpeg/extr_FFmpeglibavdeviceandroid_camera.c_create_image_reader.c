#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ media_status_t ;
struct TYPE_8__ {int /*<<< orphan*/  onImageAvailable; TYPE_2__* context; } ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  image_reader_window; int /*<<< orphan*/  image_reader; TYPE_5__ image_listener; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ AndroidCameraCtx ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AImageReader_getWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ AImageReader_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ AImageReader_setImageListener (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ AMEDIA_OK ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  IMAGE_FORMAT_ANDROID ; 
 int /*<<< orphan*/  MAX_BUF_COUNT ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  image_available ; 
 int /*<<< orphan*/  media_status_string (scalar_t__) ; 

__attribute__((used)) static int create_image_reader(AVFormatContext *avctx)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    media_status_t ret;

    ret = AImageReader_new(ctx->width, ctx->height, IMAGE_FORMAT_ANDROID,
                           MAX_BUF_COUNT, &ctx->image_reader);
    if (ret != AMEDIA_OK) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to create image reader, error: %s.\n", media_status_string(ret));
        return AVERROR_EXTERNAL;
    }

    ctx->image_listener.context = avctx;
    ctx->image_listener.onImageAvailable = image_available;

    ret = AImageReader_setImageListener(ctx->image_reader, &ctx->image_listener);
    if (ret != AMEDIA_OK) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to set image listener on image reader, error: %s.\n",
               media_status_string(ret));
        return AVERROR_EXTERNAL;
    }

    ret = AImageReader_getWindow(ctx->image_reader, &ctx->image_reader_window);
    if (ret != AMEDIA_OK) {
        av_log(avctx, AV_LOG_ERROR,
               "Could not get image reader window, error: %s.\n",
               media_status_string(ret));
        return AVERROR_EXTERNAL;
    }

    return 0;
}