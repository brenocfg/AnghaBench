#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct speex_params {int seq; int packet_size; } ;
struct ogg_stream {int pstart; int psize; struct speex_params* private; int /*<<< orphan*/ * buf; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  int int64_t ;
struct TYPE_11__ {scalar_t__ sample_rate; int channels; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_10__ {TYPE_1__** streams; struct ogg* priv_data; } ;
struct TYPE_9__ {TYPE_6__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_SPEEX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 void* AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT32_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 struct speex_params* av_mallocz (int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,scalar_t__) ; 
 scalar_t__ ff_alloc_extradata (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ff_vorbis_stream_comment (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int speex_header(AVFormatContext *s, int idx) {
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    struct speex_params *spxp = os->private;
    AVStream *st = s->streams[idx];
    uint8_t *p = os->buf + os->pstart;

    if (!spxp) {
        spxp = av_mallocz(sizeof(*spxp));
        if (!spxp)
            return AVERROR(ENOMEM);
        os->private = spxp;
    }

    if (spxp->seq > 1)
        return 0;

    if (spxp->seq == 0) {
        int frames_per_packet;
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id = AV_CODEC_ID_SPEEX;

        if (os->psize < 68) {
            av_log(s, AV_LOG_ERROR, "speex packet too small\n");
            return AVERROR_INVALIDDATA;
        }

        st->codecpar->sample_rate = AV_RL32(p + 36);
        if (st->codecpar->sample_rate <= 0) {
            av_log(s, AV_LOG_ERROR, "Invalid sample rate %d\n", st->codecpar->sample_rate);
            return AVERROR_INVALIDDATA;
        }
        st->codecpar->channels = AV_RL32(p + 48);
        if (st->codecpar->channels < 1 || st->codecpar->channels > 2) {
            av_log(s, AV_LOG_ERROR, "invalid channel count. Speex must be mono or stereo.\n");
            return AVERROR_INVALIDDATA;
        }
        st->codecpar->channel_layout = st->codecpar->channels == 1 ? AV_CH_LAYOUT_MONO :
                                                                     AV_CH_LAYOUT_STEREO;

        spxp->packet_size  = AV_RL32(p + 56);
        frames_per_packet  = AV_RL32(p + 64);
        if (spxp->packet_size < 0 ||
            frames_per_packet < 0 ||
            spxp->packet_size * (int64_t)frames_per_packet > INT32_MAX / 256) {
            av_log(s, AV_LOG_ERROR, "invalid packet_size, frames_per_packet %d %d\n", spxp->packet_size, frames_per_packet);
            spxp->packet_size = 0;
            return AVERROR_INVALIDDATA;
        }
        if (frames_per_packet)
            spxp->packet_size *= frames_per_packet;

        if (ff_alloc_extradata(st->codecpar, os->psize) < 0)
            return AVERROR(ENOMEM);
        memcpy(st->codecpar->extradata, p, st->codecpar->extradata_size);

        avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
    } else
        ff_vorbis_stream_comment(s, st, p, os->psize);

    spxp->seq++;
    return 1;
}