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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  const* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
struct TYPE_11__ {size_t cur_au_index; size_t nb_au_headers; size_t buf_size; size_t buf_pos; scalar_t__ timestamp; int /*<<< orphan*/  const* buf; TYPE_1__* au_headers; scalar_t__ au_headers_length_bytes; } ;
struct TYPE_10__ {size_t size; } ;
typedef  TYPE_2__ PayloadContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int FFMIN (int,int) ; 
 int MAX_AAC_HBR_FRAME_SIZE ; 
 int RTP_FLAG_MARKER ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int av_new_packet (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ rtp_parse_mp4_au (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int aac_parse_packet(AVFormatContext *ctx, PayloadContext *data,
                            AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                            const uint8_t *buf, int len, uint16_t seq,
                            int flags)
{
    int ret;


    if (!buf) {
        if (data->cur_au_index > data->nb_au_headers) {
            av_log(ctx, AV_LOG_ERROR, "Invalid parser state\n");
            return AVERROR_INVALIDDATA;
        }
        if (data->buf_size - data->buf_pos < data->au_headers[data->cur_au_index].size) {
            av_log(ctx, AV_LOG_ERROR, "Invalid AU size\n");
            return AVERROR_INVALIDDATA;
        }
        if ((ret = av_new_packet(pkt, data->au_headers[data->cur_au_index].size)) < 0) {
            av_log(ctx, AV_LOG_ERROR, "Out of memory\n");
            return ret;
        }
        memcpy(pkt->data, &data->buf[data->buf_pos], data->au_headers[data->cur_au_index].size);
        data->buf_pos += data->au_headers[data->cur_au_index].size;
        pkt->stream_index = st->index;
        data->cur_au_index++;

        if (data->cur_au_index == data->nb_au_headers) {
            data->buf_pos = 0;
            return 0;
        }

        return 1;
    }

    if (rtp_parse_mp4_au(data, buf, len)) {
        av_log(ctx, AV_LOG_ERROR, "Error parsing AU headers\n");
        return -1;
    }

    buf += data->au_headers_length_bytes + 2;
    len -= data->au_headers_length_bytes + 2;
    if (data->nb_au_headers == 1 && len < data->au_headers[0].size) {
        /* Packet is fragmented */

        if (!data->buf_pos) {
            if (data->au_headers[0].size > MAX_AAC_HBR_FRAME_SIZE) {
                av_log(ctx, AV_LOG_ERROR, "Invalid AU size\n");
                return AVERROR_INVALIDDATA;
            }

            data->buf_size = data->au_headers[0].size;
            data->timestamp = *timestamp;
        }

        if (data->timestamp != *timestamp ||
            data->au_headers[0].size != data->buf_size ||
            data->buf_pos + len > MAX_AAC_HBR_FRAME_SIZE) {
            data->buf_pos = 0;
            data->buf_size = 0;
            av_log(ctx, AV_LOG_ERROR, "Invalid packet received\n");
            return AVERROR_INVALIDDATA;
        }

        memcpy(&data->buf[data->buf_pos], buf, len);
        data->buf_pos += len;

        if (!(flags & RTP_FLAG_MARKER))
            return AVERROR(EAGAIN);

        if (data->buf_pos != data->buf_size) {
            data->buf_pos = 0;
            av_log(ctx, AV_LOG_ERROR, "Missed some packets, discarding frame\n");
            return AVERROR_INVALIDDATA;
        }

        data->buf_pos = 0;
        ret = av_new_packet(pkt, data->buf_size);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Out of memory\n");
            return ret;
        }
        pkt->stream_index = st->index;

        memcpy(pkt->data, data->buf, data->buf_size);

        return 0;
    }

    if (len < data->au_headers[0].size) {
        av_log(ctx, AV_LOG_ERROR, "First AU larger than packet size\n");
        return AVERROR_INVALIDDATA;
    }
    if ((ret = av_new_packet(pkt, data->au_headers[0].size)) < 0) {
        av_log(ctx, AV_LOG_ERROR, "Out of memory\n");
        return ret;
    }
    memcpy(pkt->data, buf, data->au_headers[0].size);
    len -= data->au_headers[0].size;
    buf += data->au_headers[0].size;
    pkt->stream_index = st->index;

    if (len > 0 && data->nb_au_headers > 1) {
        data->buf_size = FFMIN(len, sizeof(data->buf));
        memcpy(data->buf, buf, data->buf_size);
        data->cur_au_index = 1;
        data->buf_pos = 0;
        return 1;
    }

    return 0;
}