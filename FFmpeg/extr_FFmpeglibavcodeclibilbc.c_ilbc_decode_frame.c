#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_15__ {TYPE_1__* priv_data; } ;
struct TYPE_14__ {scalar_t__* data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int no_of_bytes; int /*<<< orphan*/  blockl; } ;
struct TYPE_12__ {TYPE_10__ decoder; } ;
typedef  TYPE_1__ ILBCDecContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  WebRtcIlbcfix_DecodeImpl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_10__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ilbc_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    ILBCDecContext *s  = avctx->priv_data;
    AVFrame *frame     = data;
    int ret;

    if (s->decoder.no_of_bytes > buf_size) {
        av_log(avctx, AV_LOG_ERROR, "iLBC frame too short (%u, should be %u)\n",
               buf_size, s->decoder.no_of_bytes);
        return AVERROR_INVALIDDATA;
    }

    frame->nb_samples = s->decoder.blockl;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    WebRtcIlbcfix_DecodeImpl((int16_t *) frame->data[0], (const uint16_t *) buf, &s->decoder, 1);

    *got_frame_ptr = 1;

    return s->decoder.no_of_bytes;
}