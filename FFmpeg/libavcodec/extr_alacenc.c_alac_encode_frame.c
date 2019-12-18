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

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  bits_per_raw_sample; int /*<<< orphan*/  channels; TYPE_1__* priv_data; } ;
struct TYPE_14__ {scalar_t__ nb_samples; int /*<<< orphan*/  extended_data; } ;
struct TYPE_13__ {int size; } ;
struct TYPE_12__ {scalar_t__ frame_size; int max_coded_frame_size; int verbatim; scalar_t__ extra_bits; scalar_t__ compression_level; } ;
typedef  TYPE_1__ AlacEncodeContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ DEFAULT_FRAME_SIZE ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int get_max_frame_size (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_frame (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alac_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                             const AVFrame *frame, int *got_packet_ptr)
{
    AlacEncodeContext *s = avctx->priv_data;
    int out_bytes, max_frame_size, ret;

    s->frame_size = frame->nb_samples;

    if (frame->nb_samples < DEFAULT_FRAME_SIZE)
        max_frame_size = get_max_frame_size(s->frame_size, avctx->channels,
                                            avctx->bits_per_raw_sample);
    else
        max_frame_size = s->max_coded_frame_size;

    if ((ret = ff_alloc_packet2(avctx, avpkt, 4 * max_frame_size, 0)) < 0)
        return ret;

    /* use verbatim mode for compression_level 0 */
    if (s->compression_level) {
        s->verbatim   = 0;
        s->extra_bits = avctx->bits_per_raw_sample - 16;
    } else {
        s->verbatim   = 1;
        s->extra_bits = 0;
    }

    out_bytes = write_frame(s, avpkt, frame->extended_data);

    if (out_bytes > max_frame_size) {
        /* frame too large. use verbatim mode */
        s->verbatim = 1;
        s->extra_bits = 0;
        out_bytes = write_frame(s, avpkt, frame->extended_data);
    }

    avpkt->size = out_bytes;
    *got_packet_ptr = 1;
    return 0;
}