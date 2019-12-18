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
typedef  int int64_t ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_12__ {TYPE_1__* codecpar; } ;
struct TYPE_11__ {scalar_t__ data_end; } ;
struct TYPE_10__ {int sample_rate; int channels; int bits_per_coded_sample; int bit_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ MMFContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_YAMAHA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int mmf_rate (int) ; 

__attribute__((used)) static int mmf_read_header(AVFormatContext *s)
{
    MMFContext *mmf = s->priv_data;
    unsigned int tag;
    AVIOContext *pb = s->pb;
    AVStream *st;
    int64_t size;
    int rate, params;

    tag = avio_rl32(pb);
    if (tag != MKTAG('M', 'M', 'M', 'D'))
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 4); /* file_size */

    /* Skip some unused chunks that may or may not be present */
    for (;; avio_skip(pb, size)) {
        tag  = avio_rl32(pb);
        size = avio_rb32(pb);
        if (tag == MKTAG('C', 'N', 'T', 'I'))
            continue;
        if (tag == MKTAG('O', 'P', 'D', 'A'))
            continue;
        break;
    }

    /* Tag = "ATRx", where "x" = track number */
    if ((tag & 0xffffff) == MKTAG('M', 'T', 'R', 0)) {
        av_log(s, AV_LOG_ERROR, "MIDI like format found, unsupported\n");
        return AVERROR_PATCHWELCOME;
    }
    if ((tag & 0xffffff) != MKTAG('A', 'T', 'R', 0)) {
        av_log(s, AV_LOG_ERROR, "Unsupported SMAF chunk %08x\n", tag);
        return AVERROR_PATCHWELCOME;
    }

    avio_r8(pb); /* format type */
    avio_r8(pb); /* sequence type */
    params = avio_r8(pb); /* (channel << 7) | (format << 4) | rate */
    rate   = mmf_rate(params & 0x0f);
    if (rate < 0) {
        av_log(s, AV_LOG_ERROR, "Invalid sample rate\n");
        return AVERROR_INVALIDDATA;
    }
    avio_r8(pb); /* wave base bit */
    avio_r8(pb); /* time base d */
    avio_r8(pb); /* time base g */

    /* Skip some unused chunks that may or may not be present */
    for (;; avio_skip(pb, size)) {
        tag  = avio_rl32(pb);
        size = avio_rb32(pb);
        if (tag == MKTAG('A', 't', 's', 'q'))
            continue;
        if (tag == MKTAG('A', 's', 'p', 'I'))
            continue;
        break;
    }

    /* Make sure it's followed by an Awa chunk, aka wave data */
    if ((tag & 0xffffff) != MKTAG('A', 'w', 'a', 0)) {
        av_log(s, AV_LOG_ERROR, "Unexpected SMAF chunk %08x\n", tag);
        return AVERROR_INVALIDDATA;
    }
    mmf->data_end = avio_tell(pb) + size;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type            = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id              = AV_CODEC_ID_ADPCM_YAMAHA;
    st->codecpar->sample_rate           = rate;
    st->codecpar->channels              = (params >> 7) + 1;
    st->codecpar->channel_layout        = params >> 7 ? AV_CH_LAYOUT_STEREO : AV_CH_LAYOUT_MONO;
    st->codecpar->bits_per_coded_sample = 4;
    st->codecpar->bit_rate              = st->codecpar->sample_rate *
                                          st->codecpar->bits_per_coded_sample;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}