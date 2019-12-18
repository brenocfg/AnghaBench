#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_10__ {int sample_rate; int channels; int bits_per_coded_sample; int bit_rate; int block_align; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_8__ {TYPE_4__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_IMA_APC ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_get_extradata (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int apc_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVStream *st;

    avio_rl32(pb); /* CRYO */
    avio_rl32(pb); /* _APC */
    avio_rl32(pb); /* 1.20 */

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_ADPCM_IMA_APC;

    avio_rl32(pb); /* number of samples */
    st->codecpar->sample_rate = avio_rl32(pb);

    /* initial predictor values for adpcm decoder */
    if (ff_get_extradata(s, st->codecpar, pb, 2 * 4) < 0)
        return AVERROR(ENOMEM);

    if (avio_rl32(pb)) {
        st->codecpar->channels       = 2;
        st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
    } else {
        st->codecpar->channels       = 1;
        st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
    }

    st->codecpar->bits_per_coded_sample = 4;
    st->codecpar->bit_rate = (int64_t)st->codecpar->bits_per_coded_sample * st->codecpar->channels
                          * st->codecpar->sample_rate;
    st->codecpar->block_align = 1;

    return 0;
}