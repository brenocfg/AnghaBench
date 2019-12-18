#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pic; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ XanContext ;
struct TYPE_12__ {TYPE_1__* priv_data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_frame_ref (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ff_reget_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xan_decode_frame_type0 (TYPE_3__*) ; 
 int xan_decode_frame_type1 (TYPE_3__*) ; 

__attribute__((used)) static int xan_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    XanContext *s = avctx->priv_data;
    int ftype;
    int ret;

    if ((ret = ff_reget_buffer(avctx, s->pic, 0)) < 0)
        return ret;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);
    ftype = bytestream2_get_le32(&s->gb);
    switch (ftype) {
    case 0:
        ret = xan_decode_frame_type0(avctx);
        break;
    case 1:
        ret = xan_decode_frame_type1(avctx);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown frame type %d\n", ftype);
        return AVERROR_INVALIDDATA;
    }
    if (ret)
        return ret;

    if ((ret = av_frame_ref(data, s->pic)) < 0)
        return ret;

    *got_frame = 1;

    return avpkt->size;
}