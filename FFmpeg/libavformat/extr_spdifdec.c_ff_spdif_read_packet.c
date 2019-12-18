#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum IEC61937DataType { ____Placeholder_IEC61937DataType } IEC61937DataType ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_21__ {int bit_rate; TYPE_3__** streams; int /*<<< orphan*/  nb_streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_20__ {int pos; int size; scalar_t__ data; } ;
struct TYPE_19__ {TYPE_1__* codecpar; } ;
struct TYPE_18__ {TYPE_2__* codecpar; } ;
struct TYPE_17__ {int codec_id; int sample_rate; } ;
struct TYPE_16__ {int codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int AV_BSWAP16C (int /*<<< orphan*/ ) ; 
 int BURST_HEADER_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  SYNCWORD1 ; 
 int /*<<< orphan*/  SYNCWORD2 ; 
 int av_new_packet (TYPE_5__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 TYPE_4__* avformat_new_stream (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  ff_spdif_bswap_buf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int spdif_get_offset_and_codec (TYPE_6__*,int,scalar_t__,int*,int*) ; 

int ff_spdif_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIOContext *pb = s->pb;
    enum IEC61937DataType data_type;
    enum AVCodecID codec_id;
    uint32_t state = 0;
    int pkt_size_bits, offset, ret;

    while (state != (AV_BSWAP16C(SYNCWORD1) << 16 | AV_BSWAP16C(SYNCWORD2))) {
        state = (state << 8) | avio_r8(pb);
        if (avio_feof(pb))
            return AVERROR_EOF;
    }

    data_type = avio_rl16(pb);
    pkt_size_bits = avio_rl16(pb);

    if (pkt_size_bits % 16)
        avpriv_request_sample(s, "Packet not ending at a 16-bit boundary");

    ret = av_new_packet(pkt, FFALIGN(pkt_size_bits, 16) >> 3);
    if (ret)
        return ret;

    pkt->pos = avio_tell(pb) - BURST_HEADER_SIZE;

    if (avio_read(pb, pkt->data, pkt->size) < pkt->size) {
        av_packet_unref(pkt);
        return AVERROR_EOF;
    }
    ff_spdif_bswap_buf16((uint16_t *)pkt->data, (uint16_t *)pkt->data, pkt->size >> 1);

    ret = spdif_get_offset_and_codec(s, data_type, pkt->data,
                                     &offset, &codec_id);
    if (ret) {
        av_packet_unref(pkt);
        return ret;
    }

    /* skip over the padding to the beginning of the next frame */
    avio_skip(pb, offset - pkt->size - BURST_HEADER_SIZE);

    if (!s->nb_streams) {
        /* first packet, create a stream */
        AVStream *st = avformat_new_stream(s, NULL);
        if (!st) {
            av_packet_unref(pkt);
            return AVERROR(ENOMEM);
        }
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id = codec_id;
    } else if (codec_id != s->streams[0]->codecpar->codec_id) {
        avpriv_report_missing_feature(s, "Codec change in IEC 61937");
        return AVERROR_PATCHWELCOME;
    }

    if (!s->bit_rate && s->streams[0]->codecpar->sample_rate)
        /* stream bitrate matches 16-bit stereo PCM bitrate for currently
           supported codecs */
        s->bit_rate = 2 * 16 * s->streams[0]->codecpar->sample_rate;

    return 0;
}