#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {scalar_t__ data_end; int block_duration; } ;
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_5__* priv_data; TYPE_2__** streams; } ;
struct TYPE_12__ {int duration; scalar_t__ stream_index; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int block_align; int codec_id; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AIFFInputContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
#define  AV_CODEC_ID_ADPCM_IMA_QT 131 
#define  AV_CODEC_ID_GSM 130 
#define  AV_CODEC_ID_QCELP 129 
#define  AV_CODEC_ID_QDM2 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int FFMIN (scalar_t__,int) ; 
 int MAX_SIZE ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aiff_read_packet(AVFormatContext *s,
                            AVPacket *pkt)
{
    AVStream *st = s->streams[0];
    AIFFInputContext *aiff = s->priv_data;
    int64_t max_size;
    int res, size;

    /* calculate size of remaining data */
    max_size = aiff->data_end - avio_tell(s->pb);
    if (max_size <= 0)
        return AVERROR_EOF;

    if (!st->codecpar->block_align) {
        av_log(s, AV_LOG_ERROR, "block_align not set\n");
        return AVERROR_INVALIDDATA;
    }

    /* Now for that packet */
    switch (st->codecpar->codec_id) {
    case AV_CODEC_ID_ADPCM_IMA_QT:
    case AV_CODEC_ID_GSM:
    case AV_CODEC_ID_QDM2:
    case AV_CODEC_ID_QCELP:
        size = st->codecpar->block_align;
        break;
    default:
        size = st->codecpar->block_align ? (MAX_SIZE / st->codecpar->block_align) * st->codecpar->block_align : MAX_SIZE;
    }
    size = FFMIN(max_size, size);
    res = av_get_packet(s->pb, pkt, size);
    if (res < 0)
        return res;

    if (size >= st->codecpar->block_align)
        pkt->flags &= ~AV_PKT_FLAG_CORRUPT;
    /* Only one stream in an AIFF file */
    pkt->stream_index = 0;
    pkt->duration     = (res / st->codecpar->block_align) * aiff->block_duration;
    return 0;
}