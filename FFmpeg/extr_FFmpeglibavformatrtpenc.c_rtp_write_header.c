#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int const codec_id; scalar_t__ codec_type; int sample_rate; int extradata_size; int* extradata; int channels; int block_align; } ;
struct TYPE_12__ {scalar_t__ id; TYPE_7__* codecpar; } ;
struct TYPE_11__ {int nb_streams; scalar_t__ payload_type; int base_timestamp; int timestamp; int ssrc; int first_packet; int start_time_realtime; int seq; int flags; int packet_size; int max_payload_size; int nal_length_size; int max_frames_per_packet; scalar_t__ buf; int /*<<< orphan*/  strict_std_compliance; scalar_t__ buf_ptr; TYPE_1__* pb; scalar_t__ first_rtcp_ntp_time; scalar_t__ cur_timestamp; TYPE_3__** streams; struct TYPE_11__* priv_data; } ;
struct TYPE_10__ {int max_packet_size; } ;
typedef  TYPE_2__ RTPMuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXPERIMENTAL ; 
 int AVFMT_FLAG_BITEXACT ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
#define  AV_CODEC_ID_AAC 145 
#define  AV_CODEC_ID_ADPCM_G722 144 
#define  AV_CODEC_ID_AMR_NB 143 
#define  AV_CODEC_ID_AMR_WB 142 
#define  AV_CODEC_ID_DIRAC 141 
#define  AV_CODEC_ID_H261 140 
#define  AV_CODEC_ID_H264 139 
#define  AV_CODEC_ID_HEVC 138 
#define  AV_CODEC_ID_ILBC 137 
#define  AV_CODEC_ID_MP2 136 
#define  AV_CODEC_ID_MP3 135 
#define  AV_CODEC_ID_MPEG1VIDEO 134 
#define  AV_CODEC_ID_MPEG2TS 133 
#define  AV_CODEC_ID_MPEG2VIDEO 132 
#define  AV_CODEC_ID_OPUS 131 
#define  AV_CODEC_ID_THEORA 130 
#define  AV_CODEC_ID_VORBIS 129 
#define  AV_CODEC_ID_VP9 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  FF_COMPLIANCE_EXPERIMENTAL ; 
 scalar_t__ NTP_OFFSET_US ; 
 scalar_t__ RTP_PT_PRIVATE ; 
 int TS_PACKET_SIZE ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int av_get_random_seed () ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_malloc (int) ; 
 int /*<<< orphan*/  avcodec_get_name (int const) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 scalar_t__ ff_ntp_time () ; 
 scalar_t__ ff_rtp_get_payload_type (TYPE_2__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  is_supported (int const) ; 

__attribute__((used)) static int rtp_write_header(AVFormatContext *s1)
{
    RTPMuxContext *s = s1->priv_data;
    int n, ret = AVERROR(EINVAL);
    AVStream *st;

    if (s1->nb_streams != 1) {
        av_log(s1, AV_LOG_ERROR, "Only one stream supported in the RTP muxer\n");
        return AVERROR(EINVAL);
    }
    st = s1->streams[0];
    if (!is_supported(st->codecpar->codec_id)) {
        av_log(s1, AV_LOG_ERROR, "Unsupported codec %s\n", avcodec_get_name(st->codecpar->codec_id));

        return -1;
    }

    if (s->payload_type < 0) {
        /* Re-validate non-dynamic payload types */
        if (st->id < RTP_PT_PRIVATE)
            st->id = ff_rtp_get_payload_type(s1, st->codecpar, -1);

        s->payload_type = st->id;
    } else {
        /* private option takes priority */
        st->id = s->payload_type;
    }

    s->base_timestamp = av_get_random_seed();
    s->timestamp = s->base_timestamp;
    s->cur_timestamp = 0;
    if (!s->ssrc)
        s->ssrc = av_get_random_seed();
    s->first_packet = 1;
    s->first_rtcp_ntp_time = ff_ntp_time();
    if (s1->start_time_realtime != 0  &&  s1->start_time_realtime != AV_NOPTS_VALUE)
        /* Round the NTP time to whole milliseconds. */
        s->first_rtcp_ntp_time = (s1->start_time_realtime / 1000) * 1000 +
                                 NTP_OFFSET_US;
    // Pick a random sequence start number, but in the lower end of the
    // available range, so that any wraparound doesn't happen immediately.
    // (Immediate wraparound would be an issue for SRTP.)
    if (s->seq < 0) {
        if (s1->flags & AVFMT_FLAG_BITEXACT) {
            s->seq = 0;
        } else
            s->seq = av_get_random_seed() & 0x0fff;
    } else
        s->seq &= 0xffff; // Use the given parameter, wrapped to the right interval

    if (s1->packet_size) {
        if (s1->pb->max_packet_size)
            s1->packet_size = FFMIN(s1->packet_size,
                                    s1->pb->max_packet_size);
    } else
        s1->packet_size = s1->pb->max_packet_size;
    if (s1->packet_size <= 12) {
        av_log(s1, AV_LOG_ERROR, "Max packet size %u too low\n", s1->packet_size);
        return AVERROR(EIO);
    }
    s->buf = av_malloc(s1->packet_size);
    if (!s->buf) {
        return AVERROR(ENOMEM);
    }
    s->max_payload_size = s1->packet_size - 12;

    if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        avpriv_set_pts_info(st, 32, 1, st->codecpar->sample_rate);
    } else {
        avpriv_set_pts_info(st, 32, 1, 90000);
    }
    s->buf_ptr = s->buf;
    switch(st->codecpar->codec_id) {
    case AV_CODEC_ID_MP2:
    case AV_CODEC_ID_MP3:
        s->buf_ptr = s->buf + 4;
        avpriv_set_pts_info(st, 32, 1, 90000);
        break;
    case AV_CODEC_ID_MPEG1VIDEO:
    case AV_CODEC_ID_MPEG2VIDEO:
        break;
    case AV_CODEC_ID_MPEG2TS:
        n = s->max_payload_size / TS_PACKET_SIZE;
        if (n < 1)
            n = 1;
        s->max_payload_size = n * TS_PACKET_SIZE;
        break;
    case AV_CODEC_ID_DIRAC:
        if (s1->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL) {
            av_log(s, AV_LOG_ERROR,
                   "Packetizing VC-2 is experimental and does not use all values "
                   "of the specification "
                   "(even though most receivers may handle it just fine). "
                   "Please set -strict experimental in order to enable it.\n");
            ret = AVERROR_EXPERIMENTAL;
            goto fail;
        }
        break;
    case AV_CODEC_ID_H261:
        if (s1->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL) {
            av_log(s, AV_LOG_ERROR,
                   "Packetizing H.261 is experimental and produces incorrect "
                   "packetization for cases where GOBs don't fit into packets "
                   "(even though most receivers may handle it just fine). "
                   "Please set -f_strict experimental in order to enable it.\n");
            ret = AVERROR_EXPERIMENTAL;
            goto fail;
        }
        break;
    case AV_CODEC_ID_H264:
        /* check for H.264 MP4 syntax */
        if (st->codecpar->extradata_size > 4 && st->codecpar->extradata[0] == 1) {
            s->nal_length_size = (st->codecpar->extradata[4] & 0x03) + 1;
        }
        break;
    case AV_CODEC_ID_HEVC:
        /* Only check for the standardized hvcC version of extradata, keeping
         * things simple and similar to the avcC/H.264 case above, instead
         * of trying to handle the pre-standardization versions (as in
         * libavcodec/hevc.c). */
        if (st->codecpar->extradata_size > 21 && st->codecpar->extradata[0] == 1) {
            s->nal_length_size = (st->codecpar->extradata[21] & 0x03) + 1;
        }
        break;
    case AV_CODEC_ID_VP9:
        if (s1->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL) {
            av_log(s, AV_LOG_ERROR,
                   "Packetizing VP9 is experimental and its specification is "
                   "still in draft state. "
                   "Please set -strict experimental in order to enable it.\n");
            ret = AVERROR_EXPERIMENTAL;
            goto fail;
        }
        break;
    case AV_CODEC_ID_VORBIS:
    case AV_CODEC_ID_THEORA:
        s->max_frames_per_packet = 15;
        break;
    case AV_CODEC_ID_ADPCM_G722:
        /* Due to a historical error, the clock rate for G722 in RTP is
         * 8000, even if the sample rate is 16000. See RFC 3551. */
        avpriv_set_pts_info(st, 32, 1, 8000);
        break;
    case AV_CODEC_ID_OPUS:
        if (st->codecpar->channels > 2) {
            av_log(s1, AV_LOG_ERROR, "Multistream opus not supported in RTP\n");
            goto fail;
        }
        /* The opus RTP RFC says that all opus streams should use 48000 Hz
         * as clock rate, since all opus sample rates can be expressed in
         * this clock rate, and sample rate changes on the fly are supported. */
        avpriv_set_pts_info(st, 32, 1, 48000);
        break;
    case AV_CODEC_ID_ILBC:
        if (st->codecpar->block_align != 38 && st->codecpar->block_align != 50) {
            av_log(s1, AV_LOG_ERROR, "Incorrect iLBC block size specified\n");
            goto fail;
        }
        s->max_frames_per_packet = s->max_payload_size / st->codecpar->block_align;
        break;
    case AV_CODEC_ID_AMR_NB:
    case AV_CODEC_ID_AMR_WB:
        s->max_frames_per_packet = 50;
        if (st->codecpar->codec_id == AV_CODEC_ID_AMR_NB)
            n = 31;
        else
            n = 61;
        /* max_header_toc_size + the largest AMR payload must fit */
        if (1 + s->max_frames_per_packet + n > s->max_payload_size) {
            av_log(s1, AV_LOG_ERROR, "RTP max payload size too small for AMR\n");
            goto fail;
        }
        if (st->codecpar->channels != 1) {
            av_log(s1, AV_LOG_ERROR, "Only mono is supported\n");
            goto fail;
        }
        break;
    case AV_CODEC_ID_AAC:
        s->max_frames_per_packet = 50;
        break;
    default:
        break;
    }

    return 0;

fail:
    av_freep(&s->buf);
    return ret;
}