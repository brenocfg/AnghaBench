#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  film_sample ;
struct TYPE_17__ {int nb_streams; TYPE_3__** streams; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_16__ {size_t index; unsigned int duration; TYPE_1__* codecpar; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_15__ {int version; scalar_t__ audio_type; int audio_samplerate; int audio_channels; int audio_bits; scalar_t__ video_type; size_t video_stream_index; size_t audio_stream_index; int base_clock; int sample_count; scalar_t__ current_sample; TYPE_10__* sample_table; } ;
struct TYPE_14__ {scalar_t__ codec_type; scalar_t__ codec_id; int codec_tag; int width; int height; unsigned char channels; int sample_rate; int bits_per_coded_sample; int block_align; int bit_rate; int /*<<< orphan*/  format; } ;
struct TYPE_13__ {unsigned int sample_offset; int sample_size; size_t stream; unsigned int pts; int /*<<< orphan*/  keyframe; } ;
typedef  TYPE_2__ FilmDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
 scalar_t__ AV_CODEC_ID_ADPCM_ADX ; 
 scalar_t__ AV_CODEC_ID_CINEPAK ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 scalar_t__ AV_CODEC_ID_PCM_S16BE_PLANAR ; 
 scalar_t__ AV_CODEC_ID_PCM_S8 ; 
 scalar_t__ AV_CODEC_ID_PCM_S8_PLANAR ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGB24 ; 
 int AV_RB16 (unsigned char*) ; 
 int AV_RB32 (unsigned char*) ; 
 int CVID_TAG ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FDSC_TAG ; 
 int INT_MAX ; 
 int RAW_TAG ; 
 int STAB_TAG ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_3__*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,unsigned char) ; 
 TYPE_10__* av_malloc_array (int,int) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  film_read_close (TYPE_4__*) ; 

__attribute__((used)) static int film_read_header(AVFormatContext *s)
{
    FilmDemuxContext *film = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;
    unsigned char scratch[256];
    int i, ret;
    unsigned int data_offset;
    unsigned int audio_frame_counter;
    unsigned int video_frame_counter;

    film->sample_table = NULL;

    /* load the main FILM header */
    if (avio_read(pb, scratch, 16) != 16)
        return AVERROR(EIO);
    data_offset = AV_RB32(&scratch[4]);
    film->version = AV_RB32(&scratch[8]);

    /* load the FDSC chunk */
    if (film->version == 0) {
        /* special case for Lemmings .film files; 20-byte header */
        if (avio_read(pb, scratch, 20) != 20)
            return AVERROR(EIO);
        /* make some assumptions about the audio parameters */
        film->audio_type = AV_CODEC_ID_PCM_S8;
        film->audio_samplerate = 22050;
        film->audio_channels = 1;
        film->audio_bits = 8;
    } else {
        /* normal Saturn .cpk files; 32-byte header */
        if (avio_read(pb, scratch, 32) != 32)
            return AVERROR(EIO);
        film->audio_samplerate = AV_RB16(&scratch[24]);
        film->audio_channels = scratch[21];
        film->audio_bits = scratch[22];
        if (scratch[23] == 2 && film->audio_channels > 0)
            film->audio_type = AV_CODEC_ID_ADPCM_ADX;
        else if (film->audio_channels > 0) {
            if (film->audio_bits == 8)
                film->audio_type = AV_CODEC_ID_PCM_S8_PLANAR;
            else if (film->audio_bits == 16)
                film->audio_type = AV_CODEC_ID_PCM_S16BE_PLANAR;
            else
                film->audio_type = AV_CODEC_ID_NONE;
        } else
            film->audio_type = AV_CODEC_ID_NONE;
    }

    if (AV_RB32(&scratch[0]) != FDSC_TAG)
        return AVERROR_INVALIDDATA;

    if (AV_RB32(&scratch[8]) == CVID_TAG) {
        film->video_type = AV_CODEC_ID_CINEPAK;
    } else if (AV_RB32(&scratch[8]) == RAW_TAG) {
        film->video_type = AV_CODEC_ID_RAWVIDEO;
    } else {
        film->video_type = AV_CODEC_ID_NONE;
    }

    /* initialize the decoder streams */
    if (film->video_type) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);
        film->video_stream_index = st->index;
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id = film->video_type;
        st->codecpar->codec_tag = 0;  /* no fourcc */
        st->codecpar->width = AV_RB32(&scratch[16]);
        st->codecpar->height = AV_RB32(&scratch[12]);

        if (film->video_type == AV_CODEC_ID_RAWVIDEO) {
            if (scratch[20] == 24) {
                st->codecpar->format = AV_PIX_FMT_RGB24;
            } else {
                av_log(s, AV_LOG_ERROR, "raw video is using unhandled %dbpp\n", scratch[20]);
                return -1;
            }
        }
    }

    if (film->audio_type) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);
        film->audio_stream_index = st->index;
        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id = film->audio_type;
        st->codecpar->codec_tag = 1;
        st->codecpar->channels = film->audio_channels;
        st->codecpar->sample_rate = film->audio_samplerate;

        if (film->audio_type == AV_CODEC_ID_ADPCM_ADX) {
            st->codecpar->bits_per_coded_sample = 18 * 8 / 32;
            st->codecpar->block_align = st->codecpar->channels * 18;
            st->need_parsing = AVSTREAM_PARSE_FULL;
        } else {
            st->codecpar->bits_per_coded_sample = film->audio_bits;
            st->codecpar->block_align = st->codecpar->channels *
                st->codecpar->bits_per_coded_sample / 8;
        }

        st->codecpar->bit_rate = st->codecpar->channels * st->codecpar->sample_rate *
            st->codecpar->bits_per_coded_sample;
    }

    /* load the sample table */
    if (avio_read(pb, scratch, 16) != 16)
        return AVERROR(EIO);
    if (AV_RB32(&scratch[0]) != STAB_TAG)
        return AVERROR_INVALIDDATA;
    film->base_clock = AV_RB32(&scratch[8]);
    film->sample_count = AV_RB32(&scratch[12]);
    if(film->sample_count >= UINT_MAX / sizeof(film_sample))
        return -1;
    film->sample_table = av_malloc_array(film->sample_count, sizeof(film_sample));
    if (!film->sample_table)
        return AVERROR(ENOMEM);

    for (i = 0; i < s->nb_streams; i++) {
        st = s->streams[i];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            avpriv_set_pts_info(st, 33, 1, film->base_clock);
        else
            avpriv_set_pts_info(st, 64, 1, film->audio_samplerate);
    }

    audio_frame_counter = video_frame_counter = 0;
    for (i = 0; i < film->sample_count; i++) {
        /* load the next sample record and transfer it to an internal struct */
        if (avio_read(pb, scratch, 16) != 16) {
            ret = AVERROR(EIO);
            goto fail;
        }
        film->sample_table[i].sample_offset =
            data_offset + AV_RB32(&scratch[0]);
        film->sample_table[i].sample_size = AV_RB32(&scratch[4]);
        if (film->sample_table[i].sample_size > INT_MAX / 4) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        if (AV_RB32(&scratch[8]) == 0xFFFFFFFF) {
            film->sample_table[i].stream = film->audio_stream_index;
            film->sample_table[i].pts = audio_frame_counter;

            if (film->audio_type == AV_CODEC_ID_ADPCM_ADX)
                audio_frame_counter += (film->sample_table[i].sample_size * 32 /
                    (18 * film->audio_channels));
            else if (film->audio_type != AV_CODEC_ID_NONE)
                audio_frame_counter += (film->sample_table[i].sample_size /
                    (film->audio_channels * film->audio_bits / 8));
        } else {
            film->sample_table[i].stream = film->video_stream_index;
            film->sample_table[i].pts = AV_RB32(&scratch[8]) & 0x7FFFFFFF;
            film->sample_table[i].keyframe = (scratch[8] & 0x80) ? 0 : AVINDEX_KEYFRAME;
            video_frame_counter++;
            if (film->video_type)
                av_add_index_entry(s->streams[film->video_stream_index],
                                   film->sample_table[i].sample_offset,
                                   film->sample_table[i].pts,
                                   film->sample_table[i].sample_size, 0,
                                   film->sample_table[i].keyframe);
        }
    }

    if (film->audio_type)
        s->streams[film->audio_stream_index]->duration = audio_frame_counter;

    if (film->video_type)
        s->streams[film->video_stream_index]->duration = video_frame_counter;

    film->current_sample = 0;

    return 0;
fail:
    film_read_close(s);
    return ret;
}