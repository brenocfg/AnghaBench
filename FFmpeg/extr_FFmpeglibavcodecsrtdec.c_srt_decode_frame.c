#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  str; } ;
struct TYPE_17__ {TYPE_1__* priv_data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {scalar_t__ num_rects; } ;
struct TYPE_14__ {int /*<<< orphan*/  readorder; } ;
typedef  TYPE_1__ FFASSDecoderContext ;
typedef  TYPE_2__ AVSubtitle ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_PKT_DATA_SUBTITLE_POSITION ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int ff_ass_add_rect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int srt_to_ass (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int srt_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_sub_ptr, AVPacket *avpkt)
{
    AVSubtitle *sub = data;
    AVBPrint buffer;
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    int size, ret;
    const uint8_t *p = av_packet_get_side_data(avpkt, AV_PKT_DATA_SUBTITLE_POSITION, &size);
    FFASSDecoderContext *s = avctx->priv_data;

    if (p && size == 16) {
        x1 = AV_RL32(p     );
        y1 = AV_RL32(p +  4);
        x2 = AV_RL32(p +  8);
        y2 = AV_RL32(p + 12);
    }

    if (avpkt->size <= 0)
        return avpkt->size;

    av_bprint_init(&buffer, 0, AV_BPRINT_SIZE_UNLIMITED);

    ret = srt_to_ass(avctx, &buffer, avpkt->data, x1, y1, x2, y2);
    if (ret >= 0)
        ret = ff_ass_add_rect(sub, buffer.str, s->readorder++, 0, NULL, NULL);
    av_bprint_finalize(&buffer, NULL);
    if (ret < 0)
        return ret;

    *got_sub_ptr = sub->num_rects > 0;
    return avpkt->size;
}