#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {TYPE_1__* priv_data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_10__* frame; int /*<<< orphan*/  palette; int /*<<< orphan*/  gb; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ MmContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int AV_RL16 (int /*<<< orphan*/  const*) ; 
 int MM_PREAMBLE_SIZE ; 
#define  MM_TYPE_INTER 134 
#define  MM_TYPE_INTER_HH 133 
#define  MM_TYPE_INTER_HHV 132 
#define  MM_TYPE_INTRA 131 
#define  MM_TYPE_INTRA_HH 130 
#define  MM_TYPE_INTRA_HHV 129 
#define  MM_TYPE_PALETTE 128 
 int av_frame_ref (void*,TYPE_10__*) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mm_decode_inter (TYPE_1__*,int,int) ; 
 int mm_decode_intra (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mm_decode_pal (TYPE_1__*) ; 

__attribute__((used)) static int mm_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    MmContext *s = avctx->priv_data;
    int type, res;

    if (buf_size < MM_PREAMBLE_SIZE)
        return AVERROR_INVALIDDATA;
    type = AV_RL16(&buf[0]);
    buf += MM_PREAMBLE_SIZE;
    buf_size -= MM_PREAMBLE_SIZE;
    bytestream2_init(&s->gb, buf, buf_size);

    if ((res = ff_reget_buffer(avctx, s->frame, 0)) < 0)
        return res;

    switch(type) {
    case MM_TYPE_PALETTE   : mm_decode_pal(s); return avpkt->size;
    case MM_TYPE_INTRA     : res = mm_decode_intra(s, 0, 0); break;
    case MM_TYPE_INTRA_HH  : res = mm_decode_intra(s, 1, 0); break;
    case MM_TYPE_INTRA_HHV : res = mm_decode_intra(s, 1, 1); break;
    case MM_TYPE_INTER     : res = mm_decode_inter(s, 0, 0); break;
    case MM_TYPE_INTER_HH  : res = mm_decode_inter(s, 1, 0); break;
    case MM_TYPE_INTER_HHV : res = mm_decode_inter(s, 1, 1); break;
    default:
        res = AVERROR_INVALIDDATA;
        break;
    }
    if (res < 0)
        return res;

    memcpy(s->frame->data[1], s->palette, AVPALETTE_SIZE);

    if ((res = av_frame_ref(data, s->frame)) < 0)
        return res;

    *got_frame      = 1;

    return avpkt->size;
}