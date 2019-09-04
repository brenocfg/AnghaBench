#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  frame_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* execute ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_9__* sys; int /*<<< orphan*/  work_chunks; int /*<<< orphan*/  buf; int /*<<< orphan*/  const* frame; } ;
typedef  int /*<<< orphan*/  DVwork_chunk ;
typedef  TYPE_1__ DVVideoContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  dv_encode_video_segment ; 
 int /*<<< orphan*/  dv_format_frame (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dv_work_pool_size (TYPE_9__*) ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dvvideo_encode_frame(AVCodecContext *c, AVPacket *pkt,
                                const AVFrame *frame, int *got_packet)
{
    DVVideoContext *s = c->priv_data;
    int ret;

    if ((ret = ff_alloc_packet2(c, pkt, s->sys->frame_size, 0)) < 0)
        return ret;

    c->pix_fmt                = s->sys->pix_fmt;
    s->frame                  = frame;
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    c->coded_frame->key_frame = 1;
    c->coded_frame->pict_type = AV_PICTURE_TYPE_I;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    s->buf = pkt->data;
    c->execute(c, dv_encode_video_segment, s->work_chunks, NULL,
               dv_work_pool_size(s->sys), sizeof(DVwork_chunk));

    emms_c();

    dv_format_frame(s, pkt->data);

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}