#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* avpkt; TYPE_3__* frame; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_14__ {int channels; int /*<<< orphan*/  (* execute2 ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_13__ {int nb_samples; } ;
struct TYPE_12__ {int size; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  dsd_channel ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame_ptr, AVPacket *avpkt)
{
    ThreadData td;
    AVFrame *frame = data;
    int ret;

    frame->nb_samples = avpkt->size / avctx->channels;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    td.frame = frame;
    td.avpkt = avpkt;
    avctx->execute2(avctx, dsd_channel, &td, NULL, avctx->channels);

    *got_frame_ptr = 1;
    return frame->nb_samples * avctx->channels;
}