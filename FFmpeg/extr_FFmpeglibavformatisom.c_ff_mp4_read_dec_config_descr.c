#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {int codec_id; int extradata_size; int /*<<< orphan*/  channels; scalar_t__ sample_rate; int /*<<< orphan*/  extradata; void* bit_rate; } ;
struct TYPE_7__ {TYPE_4__* codecpar; } ;
struct TYPE_6__ {int object_type; int sampling_index; scalar_t__ ext_sample_rate; scalar_t__ sample_rate; int /*<<< orphan*/  ext_object_type; int /*<<< orphan*/  channels; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ MPEG4AudioConfig ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int MP4DecSpecificDescrTag ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__* avpriv_mpa_freq_tab ; 
 int avpriv_mpeg4audio_get_config (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 void* ff_codec_get_id (int /*<<< orphan*/ ,int) ; 
 int ff_get_extradata (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_mp4_obj_type ; 
 int ff_mp4_read_descr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mp4_audio_types ; 

int ff_mp4_read_dec_config_descr(AVFormatContext *fc, AVStream *st, AVIOContext *pb)
{
    enum AVCodecID codec_id;
    unsigned v;
    int len, tag;
    int ret;
    int object_type_id = avio_r8(pb);
    avio_r8(pb); /* stream type */
    avio_rb24(pb); /* buffer size db */

    v = avio_rb32(pb);

    // TODO: fix this with codecpar
#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
    if (v < INT32_MAX)
        st->codec->rc_max_rate = v;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    st->codecpar->bit_rate = avio_rb32(pb); /* avg bitrate */

    codec_id= ff_codec_get_id(ff_mp4_obj_type, object_type_id);
    if (codec_id)
        st->codecpar->codec_id = codec_id;
    av_log(fc, AV_LOG_TRACE, "esds object type id 0x%02x\n", object_type_id);
    len = ff_mp4_read_descr(fc, pb, &tag);
    if (tag == MP4DecSpecificDescrTag) {
        av_log(fc, AV_LOG_TRACE, "Specific MPEG-4 header len=%d\n", len);
        /* As per 14496-3:2009 9.D.2.2, No decSpecificInfo is defined
           for MPEG-1 Audio or MPEG-2 Audio; MPEG-2 AAC excluded. */
        if (object_type_id == 0x69 || object_type_id == 0x6b)
            return 0;
        if (!len || (uint64_t)len > (1<<30))
            return AVERROR_INVALIDDATA;
        if ((ret = ff_get_extradata(fc, st->codecpar, pb, len)) < 0)
            return ret;
        if (st->codecpar->codec_id == AV_CODEC_ID_AAC) {
            MPEG4AudioConfig cfg = {0};
            ret = avpriv_mpeg4audio_get_config(&cfg, st->codecpar->extradata,
                                               st->codecpar->extradata_size * 8, 1);
            if (ret < 0)
                return ret;
            st->codecpar->channels = cfg.channels;
            if (cfg.object_type == 29 && cfg.sampling_index < 3) // old mp3on4
                st->codecpar->sample_rate = avpriv_mpa_freq_tab[cfg.sampling_index];
            else if (cfg.ext_sample_rate)
                st->codecpar->sample_rate = cfg.ext_sample_rate;
            else
                st->codecpar->sample_rate = cfg.sample_rate;
            av_log(fc, AV_LOG_TRACE, "mp4a config channels %d obj %d ext obj %d "
                    "sample rate %d ext sample rate %d\n", st->codecpar->channels,
                    cfg.object_type, cfg.ext_object_type,
                    cfg.sample_rate, cfg.ext_sample_rate);
            if (!(st->codecpar->codec_id = ff_codec_get_id(mp4_audio_types,
                                                        cfg.object_type)))
                st->codecpar->codec_id = AV_CODEC_ID_AAC;
        }
    }
    return 0;
}