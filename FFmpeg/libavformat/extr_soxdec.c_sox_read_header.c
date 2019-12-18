#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int channels; double sample_rate; int bits_per_coded_sample; int bit_rate; int block_align; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S32BE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S32LE ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 double INT_MAX ; 
 int SOX_FIXED_HDR ; 
 void* SOX_TAG ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 double av_int2double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_malloc (unsigned int) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb64 (int /*<<< orphan*/ *) ; 
 unsigned int avio_read (int /*<<< orphan*/ *,char*,unsigned int) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,double) ; 
 double floor (double) ; 

__attribute__((used)) static int sox_read_header(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    unsigned header_size, comment_size;
    double sample_rate, sample_rate_frac;
    AVStream *st;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;

    if (avio_rl32(pb) == SOX_TAG) {
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S32LE;
        header_size         = avio_rl32(pb);
        avio_skip(pb, 8); /* sample count */
        sample_rate         = av_int2double(avio_rl64(pb));
        st->codecpar->channels = avio_rl32(pb);
        comment_size        = avio_rl32(pb);
    } else {
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S32BE;
        header_size         = avio_rb32(pb);
        avio_skip(pb, 8); /* sample count */
        sample_rate         = av_int2double(avio_rb64(pb));
        st->codecpar->channels = avio_rb32(pb);
        comment_size        = avio_rb32(pb);
    }

    if (comment_size > 0xFFFFFFFFU - SOX_FIXED_HDR - 4U) {
        av_log(s, AV_LOG_ERROR, "invalid comment size (%u)\n", comment_size);
        return AVERROR_INVALIDDATA;
    }

    if (sample_rate <= 0 || sample_rate > INT_MAX) {
        av_log(s, AV_LOG_ERROR, "invalid sample rate (%f)\n", sample_rate);
        return AVERROR_INVALIDDATA;
    }

    sample_rate_frac = sample_rate - floor(sample_rate);
    if (sample_rate_frac)
        av_log(s, AV_LOG_WARNING,
               "truncating fractional part of sample rate (%f)\n",
               sample_rate_frac);

    if ((header_size + 4) & 7 || header_size < SOX_FIXED_HDR + comment_size
        || st->codecpar->channels > 65535) /* Reserve top 16 bits */ {
        av_log(s, AV_LOG_ERROR, "invalid header\n");
        return AVERROR_INVALIDDATA;
    }

    if (comment_size && comment_size < UINT_MAX) {
        char *comment = av_malloc(comment_size+1);
        if(!comment)
            return AVERROR(ENOMEM);
        if (avio_read(pb, comment, comment_size) != comment_size) {
            av_freep(&comment);
            return AVERROR(EIO);
        }
        comment[comment_size] = 0;

        av_dict_set(&s->metadata, "comment", comment,
                               AV_DICT_DONT_STRDUP_VAL);
    }

    avio_skip(pb, header_size - SOX_FIXED_HDR - comment_size);

    st->codecpar->sample_rate           = sample_rate;
    st->codecpar->bits_per_coded_sample = 32;
    st->codecpar->bit_rate              = (int64_t)st->codecpar->sample_rate *
                                          st->codecpar->bits_per_coded_sample *
                                          st->codecpar->channels;
    st->codecpar->block_align           = st->codecpar->bits_per_coded_sample *
                                          st->codecpar->channels / 8;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}