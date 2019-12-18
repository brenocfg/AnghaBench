#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t current_stream; int* start_channel; int* offset; int num_streams; int /*<<< orphan*/ ** samples; TYPE_8__* xma; TYPE_2__** frames; } ;
typedef  TYPE_1__ XMADecodeCtx ;
struct TYPE_13__ {int nb_channels; scalar_t__ skip_packets; scalar_t__ packet_loss; scalar_t__ packet_done; } ;
struct TYPE_12__ {TYPE_1__* priv_data; } ;
struct TYPE_11__ {int nb_samples; int /*<<< orphan*/ ** extended_data; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ FFMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int FFMIN (int,int) ; 
 int INT_MAX ; 
 int decode_packet (TYPE_3__*,TYPE_8__*,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xma_decode_packet(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    XMADecodeCtx *s = avctx->priv_data;
    int got_stream_frame_ptr = 0;
    AVFrame *frame = data;
    int i, ret, offset = INT_MAX;

    if (!s->frames[s->current_stream]->data[0]) {
        s->frames[s->current_stream]->nb_samples = 512;
        if ((ret = ff_get_buffer(avctx, s->frames[s->current_stream], 0)) < 0) {
            return ret;
        }
    }
    /* decode current stream packet */
    ret = decode_packet(avctx, &s->xma[s->current_stream], s->frames[s->current_stream],
                        &got_stream_frame_ptr, avpkt);

    /* copy stream samples (1/2ch) to sample buffer (Nch) */
    if (got_stream_frame_ptr) {
        int start_ch = s->start_channel[s->current_stream];
        memcpy(&s->samples[start_ch + 0][s->offset[s->current_stream] * 512],
               s->frames[s->current_stream]->extended_data[0], 512 * 4);
        if (s->xma[s->current_stream].nb_channels > 1)
            memcpy(&s->samples[start_ch + 1][s->offset[s->current_stream] * 512],
                   s->frames[s->current_stream]->extended_data[1], 512 * 4);
        s->offset[s->current_stream]++;
    } else if (ret < 0) {
        memset(s->offset, 0, sizeof(s->offset));
        s->current_stream = 0;
        return ret;
    }

    /* find next XMA packet's owner stream, and update.
     * XMA streams find their packets following packet_skips
     * (at start there is one packet per stream, then interleave non-linearly). */
    if (s->xma[s->current_stream].packet_done ||
        s->xma[s->current_stream].packet_loss) {

        /* select stream with 0 skip_packets (= uses next packet) */
        if (s->xma[s->current_stream].skip_packets != 0) {
            int min[2];

            min[0] = s->xma[0].skip_packets;
            min[1] = i = 0;

            for (i = 1; i < s->num_streams; i++) {
                if (s->xma[i].skip_packets < min[0]) {
                    min[0] = s->xma[i].skip_packets;
                    min[1] = i;
                }
            }

            s->current_stream = min[1];
        }

        /* all other streams skip next packet */
        for (i = 0; i < s->num_streams; i++) {
            s->xma[i].skip_packets = FFMAX(0, s->xma[i].skip_packets - 1);
        }

        /* copy samples from buffer to output if possible */
        for (i = 0; i < s->num_streams; i++) {
            offset = FFMIN(offset, s->offset[i]);
        }
        if (offset > 0) {
            int bret;

            frame->nb_samples = 512 * offset;
            if ((bret = ff_get_buffer(avctx, frame, 0)) < 0)
                return bret;

            /* copy samples buffer (Nch) to frame samples (Nch), move unconsumed samples */
            for (i = 0; i < s->num_streams; i++) {
                int start_ch = s->start_channel[i];
                memcpy(frame->extended_data[start_ch + 0], s->samples[start_ch + 0], frame->nb_samples * 4);
                if (s->xma[i].nb_channels > 1)
                    memcpy(frame->extended_data[start_ch + 1], s->samples[start_ch + 1], frame->nb_samples * 4);

                s->offset[i] -= offset;
                if (s->offset[i]) {
                    memmove(s->samples[start_ch + 0], s->samples[start_ch + 0] + frame->nb_samples, s->offset[i] * 4 * 512);
                    if (s->xma[i].nb_channels > 1)
                        memmove(s->samples[start_ch + 1], s->samples[start_ch + 1] + frame->nb_samples, s->offset[i] * 4 * 512);
                }
            }

            *got_frame_ptr = 1;
        }
    }

    return ret;
}