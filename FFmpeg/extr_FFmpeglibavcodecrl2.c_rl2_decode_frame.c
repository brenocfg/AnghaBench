#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {TYPE_1__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int /*<<< orphan*/  palette; int /*<<< orphan*/  video_base; } ;
typedef  TYPE_1__ Rl2Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl2_rle_decode (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rl2_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int ret, buf_size  = avpkt->size;
    Rl2Context *s = avctx->priv_data;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    /** run length decode */
    rl2_rle_decode(s, buf, buf_size, frame->data[0], frame->linesize[0],
                   s->video_base);

    /** make the palette available on the way out */
    memcpy(frame->data[1], s->palette, AVPALETTE_SIZE);

    *got_frame = 1;

    /** report that the buffer was completely consumed */
    return buf_size;
}