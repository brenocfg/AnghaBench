#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_frame_move_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/  wrapped_avframe_release_buffer ; 

__attribute__((used)) static int wrapped_avframe_encode(AVCodecContext *avctx, AVPacket *pkt,
                     const AVFrame *frame, int *got_packet)
{
    AVFrame *wrapped = av_frame_clone(frame);
    uint8_t *data;
    int size = sizeof(*wrapped) + AV_INPUT_BUFFER_PADDING_SIZE;

    if (!wrapped)
        return AVERROR(ENOMEM);

    data = av_mallocz(size);
    if (!data) {
        av_frame_free(&wrapped);
        return AVERROR(ENOMEM);
    }

    pkt->buf = av_buffer_create(data, size,
                                wrapped_avframe_release_buffer, NULL,
                                AV_BUFFER_FLAG_READONLY);
    if (!pkt->buf) {
        av_frame_free(&wrapped);
        av_freep(&data);
        return AVERROR(ENOMEM);
    }

    av_frame_move_ref((AVFrame*)data, wrapped);
    av_frame_free(&wrapped);

    pkt->data = data;
    pkt->size = sizeof(*wrapped);

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}