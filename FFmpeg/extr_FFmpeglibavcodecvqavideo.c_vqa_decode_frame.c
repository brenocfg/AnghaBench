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
struct TYPE_11__ {int /*<<< orphan*/  palette; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ VqaContext ;
struct TYPE_14__ {TYPE_1__* priv_data; } ;
struct TYPE_13__ {int palette_has_changed; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int PALETTE_COUNT ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vqa_decode_chunk (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static int vqa_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    VqaContext *s = avctx->priv_data;
    AVFrame *frame = data;
    int res;

    if ((res = ff_get_buffer(avctx, frame, 0)) < 0)
        return res;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);
    if ((res = vqa_decode_chunk(s, frame)) < 0)
        return res;

    /* make the palette available on the way out */
    memcpy(frame->data[1], s->palette, PALETTE_COUNT * 4);
    frame->palette_has_changed = 1;

    *got_frame      = 1;

    /* report that the buffer was completely consumed */
    return avpkt->size;
}