#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int* data; int size; int /*<<< orphan*/  stream_index; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; TYPE_1__* codecpar; } ;
struct TYPE_7__ {scalar_t__ codec_id; int channels; int /*<<< orphan*/  channel_layout; } ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 scalar_t__ AV_CODEC_ID_AMR_NB ; 
 scalar_t__ AV_CODEC_ID_AMR_WB ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_new_packet (TYPE_3__*,int) ; 
 int* frame_sizes_nb ; 
 int* frame_sizes_wb ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amr_handle_packet(AVFormatContext *ctx, PayloadContext *data,
                             AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                             const uint8_t *buf, int len, uint16_t seq,
                             int flags)
{
    const uint8_t *frame_sizes = NULL;
    int frames;
    int i;
    const uint8_t *speech_data;
    uint8_t *ptr;

    if (st->codecpar->codec_id == AV_CODEC_ID_AMR_NB) {
        frame_sizes = frame_sizes_nb;
    } else if (st->codecpar->codec_id == AV_CODEC_ID_AMR_WB) {
        frame_sizes = frame_sizes_wb;
    } else {
        av_log(ctx, AV_LOG_ERROR, "Bad codec ID\n");
        return AVERROR_INVALIDDATA;
    }

    if (st->codecpar->channels != 1) {
        av_log(ctx, AV_LOG_ERROR, "Only mono AMR is supported\n");
        return AVERROR_INVALIDDATA;
    }
    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;

    /* The AMR RTP packet consists of one header byte, followed
     * by one TOC byte for each AMR frame in the packet, followed
     * by the speech data for all the AMR frames.
     *
     * The header byte contains only a codec mode request, for
     * requesting what kind of AMR data the sender wants to
     * receive. Not used at the moment.
     */

    /* Count the number of frames in the packet. The highest bit
     * is set in a TOC byte if there are more frames following.
     */
    for (frames = 1; frames < len && (buf[frames] & 0x80); frames++) ;

    if (1 + frames >= len) {
        /* We hit the end of the packet while counting frames. */
        av_log(ctx, AV_LOG_ERROR, "No speech data found\n");
        return AVERROR_INVALIDDATA;
    }

    speech_data = buf + 1 + frames;

    /* Everything except the codec mode request byte should be output. */
    if (av_new_packet(pkt, len - 1)) {
        av_log(ctx, AV_LOG_ERROR, "Out of memory\n");
        return AVERROR(ENOMEM);
    }
    pkt->stream_index = st->index;
    ptr = pkt->data;

    for (i = 0; i < frames; i++) {
        uint8_t toc = buf[1 + i];
        int frame_size = frame_sizes[(toc >> 3) & 0x0f];

        if (speech_data + frame_size > buf + len) {
            /* Too little speech data */
            av_log(ctx, AV_LOG_WARNING, "Too little speech data in the RTP packet\n");
            /* Set the unwritten part of the packet to zero. */
            memset(ptr, 0, pkt->data + pkt->size - ptr);
            pkt->size = ptr - pkt->data;
            return 0;
        }

        /* Extract the AMR frame mode from the TOC byte */
        *ptr++ = toc & 0x7C;

        /* Copy the speech data */
        memcpy(ptr, speech_data, frame_size);
        speech_data += frame_size;
        ptr += frame_size;
    }

    if (speech_data < buf + len) {
        av_log(ctx, AV_LOG_WARNING, "Too much speech data in the RTP packet?\n");
        /* Set the unwritten part of the packet to zero. */
        memset(ptr, 0, pkt->data + pkt->size - ptr);
        pkt->size = ptr - pkt->data;
    }

    return 0;
}