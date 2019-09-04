#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  VTHWFrame ;
struct TYPE_11__ {int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* private_ref; int /*<<< orphan*/ ** buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  post_process; } ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_2__ FrameDecodeData ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_mallocz (size_t) ; 
 int ff_attach_decode_data (TYPE_3__*) ; 
 int /*<<< orphan*/  videotoolbox_buffer_release ; 
 int /*<<< orphan*/  videotoolbox_postproc_frame ; 

int ff_videotoolbox_alloc_frame(AVCodecContext *avctx, AVFrame *frame)
{
    size_t      size = sizeof(VTHWFrame);
    uint8_t    *data = NULL;
    AVBufferRef *buf = NULL;
    int ret = ff_attach_decode_data(frame);
    FrameDecodeData *fdd;
    if (ret < 0)
        return ret;

    data = av_mallocz(size);
    if (!data)
        return AVERROR(ENOMEM);
    buf = av_buffer_create(data, size, videotoolbox_buffer_release, NULL, 0);
    if (!buf) {
        av_freep(&data);
        return AVERROR(ENOMEM);
    }
    frame->buf[0] = buf;

    fdd = (FrameDecodeData*)frame->private_ref->data;
    fdd->post_process = videotoolbox_postproc_frame;

    frame->width  = avctx->width;
    frame->height = avctx->height;
    frame->format = avctx->pix_fmt;

    return 0;
}