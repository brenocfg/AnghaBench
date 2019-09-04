#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_17__ {long long bit_rate; int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_16__ {int duration; int size; int /*<<< orphan*/  data; scalar_t__ stream_index; int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {TYPE_1__* codecpar; } ;
struct TYPE_14__ {int counter; int packet_size; scalar_t__ dss_sp_swap_byte; scalar_t__ dss_sp_buf; scalar_t__ swap; } ;
struct TYPE_13__ {long long sample_rate; } ;
typedef  TYPE_2__ DSSDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int DSS_FRAME_SIZE ; 
 int /*<<< orphan*/  EAGAIN ; 
 int av_new_packet (TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int avio_read (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_skip_audio_header (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dss_sp_byte_swap (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dss_sp_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    DSSDemuxContext *ctx = s->priv_data;
    AVStream *st = s->streams[0];
    int read_size, ret, offset = 0, buff_offset = 0;
    int64_t pos = avio_tell(s->pb);

    if (ctx->counter == 0)
        dss_skip_audio_header(s, pkt);

    if (ctx->swap) {
        read_size   = DSS_FRAME_SIZE - 2;
        buff_offset = 3;
    } else
        read_size = DSS_FRAME_SIZE;

    ctx->counter -= read_size;
    ctx->packet_size = DSS_FRAME_SIZE - 1;

    ret = av_new_packet(pkt, DSS_FRAME_SIZE);
    if (ret < 0)
        return ret;

    pkt->duration     = 264;
    pkt->pos = pos;
    pkt->stream_index = 0;
    s->bit_rate = 8LL * ctx->packet_size * st->codecpar->sample_rate * 512 / (506 * pkt->duration);

    if (ctx->counter < 0) {
        int size2 = ctx->counter + read_size;

        ret = avio_read(s->pb, ctx->dss_sp_buf + offset + buff_offset,
                        size2 - offset);
        if (ret < size2 - offset)
            goto error_eof;

        dss_skip_audio_header(s, pkt);
        offset = size2;
    }

    ret = avio_read(s->pb, ctx->dss_sp_buf + offset + buff_offset,
                    read_size - offset);
    if (ret < read_size - offset)
        goto error_eof;

    dss_sp_byte_swap(ctx, pkt->data, ctx->dss_sp_buf);

    if (ctx->dss_sp_swap_byte < 0) {
        ret = AVERROR(EAGAIN);
        goto error_eof;
    }

    return pkt->size;

error_eof:
    av_packet_unref(pkt);
    return ret < 0 ? ret : AVERROR_EOF;
}