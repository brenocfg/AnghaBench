#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  long long uint64_t ;
struct TYPE_5__ {long long sample_rate; int bits_per_coded_sample; int codec_tag; long long bit_rate; int /*<<< orphan*/  codec_id; void* channels; scalar_t__* extradata; void* block_align; int /*<<< orphan*/  codec_type; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_AAC_LATM ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_G726 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL16 (scalar_t__*) ; 
 long long AV_RL32 (scalar_t__*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_freep (scalar_t__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,long long) ; 
 void* avio_rb16 (int /*<<< orphan*/ *) ; 
 long long avio_rb32 (int /*<<< orphan*/ *) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 long long avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ff_get_extradata (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_wav_codec_get_id (int,int) ; 
 int /*<<< orphan*/  parse_waveformatex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

int ff_get_wav_header(AVFormatContext *s, AVIOContext *pb,
                      AVCodecParameters *par, int size, int big_endian)
{
    int id;
    uint64_t bitrate = 0;

    if (size < 14) {
        avpriv_request_sample(s, "wav header size < 14");
        return AVERROR_INVALIDDATA;
    }

    par->codec_type  = AVMEDIA_TYPE_AUDIO;
    if (!big_endian) {
        id                 = avio_rl16(pb);
        if (id != 0x0165) {
            par->channels    = avio_rl16(pb);
            par->sample_rate = avio_rl32(pb);
            bitrate            = avio_rl32(pb) * 8LL;
            par->block_align = avio_rl16(pb);
        }
    } else {
        id                 = avio_rb16(pb);
        par->channels    = avio_rb16(pb);
        par->sample_rate = avio_rb32(pb);
        bitrate            = avio_rb32(pb) * 8LL;
        par->block_align = avio_rb16(pb);
    }
    if (size == 14) {  /* We're dealing with plain vanilla WAVEFORMAT */
        par->bits_per_coded_sample = 8;
    } else {
        if (!big_endian) {
            par->bits_per_coded_sample = avio_rl16(pb);
        } else {
            par->bits_per_coded_sample = avio_rb16(pb);
        }
    }
    if (id == 0xFFFE) {
        par->codec_tag = 0;
    } else {
        par->codec_tag = id;
        par->codec_id  = ff_wav_codec_get_id(id,
                                             par->bits_per_coded_sample);
    }
    if (size >= 18 && id != 0x0165) {  /* We're obviously dealing with WAVEFORMATEX */
        int cbSize = avio_rl16(pb); /* cbSize */
        if (big_endian) {
            avpriv_report_missing_feature(s, "WAVEFORMATEX support for RIFX files");
            return AVERROR_PATCHWELCOME;
        }
        size  -= 18;
        cbSize = FFMIN(size, cbSize);
        if (cbSize >= 22 && id == 0xfffe) { /* WAVEFORMATEXTENSIBLE */
            parse_waveformatex(s, pb, par);
            cbSize -= 22;
            size   -= 22;
        }
        if (cbSize > 0) {
            av_freep(&par->extradata);
            if (ff_get_extradata(s, par, pb, cbSize) < 0)
                return AVERROR(ENOMEM);
            size -= cbSize;
        }

        /* It is possible for the chunk to contain garbage at the end */
        if (size > 0)
            avio_skip(pb, size);
    } else if (id == 0x0165 && size >= 32) {
        int nb_streams, i;

        size -= 4;
        av_freep(&par->extradata);
        if (ff_get_extradata(s, par, pb, size) < 0)
            return AVERROR(ENOMEM);
        nb_streams         = AV_RL16(par->extradata + 4);
        par->sample_rate   = AV_RL32(par->extradata + 12);
        par->channels      = 0;
        bitrate            = 0;
        if (size < 8 + nb_streams * 20)
            return AVERROR_INVALIDDATA;
        for (i = 0; i < nb_streams; i++)
            par->channels += par->extradata[8 + i * 20 + 17];
    }

    par->bit_rate = bitrate;

    if (par->sample_rate <= 0) {
        av_log(s, AV_LOG_ERROR,
               "Invalid sample rate: %d\n", par->sample_rate);
        return AVERROR_INVALIDDATA;
    }
    if (par->codec_id == AV_CODEC_ID_AAC_LATM) {
        /* Channels and sample_rate values are those prior to applying SBR
         * and/or PS. */
        par->channels    = 0;
        par->sample_rate = 0;
    }
    /* override bits_per_coded_sample for G.726 */
    if (par->codec_id == AV_CODEC_ID_ADPCM_G726 && par->sample_rate)
        par->bits_per_coded_sample = par->bit_rate / par->sample_rate;

    return 0;
}