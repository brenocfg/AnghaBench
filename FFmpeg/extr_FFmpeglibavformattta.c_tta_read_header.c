#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_25__ {int channels; int sample_rate; int bits_per_coded_sample; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_24__ {int seekable; } ;
struct TYPE_23__ {int error_recognition; TYPE_5__* pb; TYPE_1__* priv_data; } ;
struct TYPE_22__ {int duration; TYPE_9__* codecpar; scalar_t__ start_time; } ;
struct TYPE_21__ {int frame_size; int last_frame_size; int totalframes; scalar_t__ currentframe; } ;
typedef  TYPE_1__ TTAContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_TTA ; 
 int AV_EF_CRCCHECK ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL32 (char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int UINT32_MAX ; 
 int UINT_MAX ; 
 int av_add_index_entry (TYPE_2__*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avio_rl16 (TYPE_5__*) ; 
 int avio_rl32 (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_5__*,int) ; 
 scalar_t__ avio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 scalar_t__ ff_alloc_extradata (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  ff_ape_parse_tag (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_crcEDB88320_update ; 
 int /*<<< orphan*/  ff_id3v1_read (TYPE_3__*) ; 
 int ffio_get_checksum (TYPE_5__*) ; 
 int /*<<< orphan*/  ffio_init_checksum (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tta_read_header(AVFormatContext *s)
{
    TTAContext *c = s->priv_data;
    AVStream *st;
    int i, channels, bps, samplerate;
    int64_t framepos, start_offset;
    uint32_t nb_samples, crc;

    ff_id3v1_read(s);

    start_offset = avio_tell(s->pb);
    if (start_offset < 0)
        return start_offset;
    ffio_init_checksum(s->pb, ff_crcEDB88320_update, UINT32_MAX);
    if (avio_rl32(s->pb) != AV_RL32("TTA1"))
        return AVERROR_INVALIDDATA;

    avio_skip(s->pb, 2); // FIXME: flags
    channels = avio_rl16(s->pb);
    bps = avio_rl16(s->pb);
    samplerate = avio_rl32(s->pb);
    if(samplerate <= 0 || samplerate > 1000000){
        av_log(s, AV_LOG_ERROR, "nonsense samplerate\n");
        return AVERROR_INVALIDDATA;
    }

    nb_samples = avio_rl32(s->pb);
    if (!nb_samples) {
        av_log(s, AV_LOG_ERROR, "invalid number of samples\n");
        return AVERROR_INVALIDDATA;
    }

    crc = ffio_get_checksum(s->pb) ^ UINT32_MAX;
    if (crc != avio_rl32(s->pb) && s->error_recognition & AV_EF_CRCCHECK) {
        av_log(s, AV_LOG_ERROR, "Header CRC error\n");
        return AVERROR_INVALIDDATA;
    }

    c->frame_size      = samplerate * 256 / 245;
    c->last_frame_size = nb_samples % c->frame_size;
    if (!c->last_frame_size)
        c->last_frame_size = c->frame_size;
    c->totalframes = nb_samples / c->frame_size + (c->last_frame_size < c->frame_size);
    c->currentframe = 0;

    if(c->totalframes >= UINT_MAX/sizeof(uint32_t) || c->totalframes <= 0){
        av_log(s, AV_LOG_ERROR, "totalframes %d invalid\n", c->totalframes);
        return AVERROR_INVALIDDATA;
    }

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avpriv_set_pts_info(st, 64, 1, samplerate);
    st->start_time = 0;
    st->duration = nb_samples;

    framepos = avio_tell(s->pb);
    if (framepos < 0)
        return framepos;
    framepos += 4 * c->totalframes + 4;

    if (ff_alloc_extradata(st->codecpar, avio_tell(s->pb) - start_offset))
        return AVERROR(ENOMEM);

    avio_seek(s->pb, start_offset, SEEK_SET);
    avio_read(s->pb, st->codecpar->extradata, st->codecpar->extradata_size);

    ffio_init_checksum(s->pb, ff_crcEDB88320_update, UINT32_MAX);
    for (i = 0; i < c->totalframes; i++) {
        uint32_t size = avio_rl32(s->pb);
        int r;
        if ((r = av_add_index_entry(st, framepos, i * c->frame_size, size, 0,
                                    AVINDEX_KEYFRAME)) < 0)
            return r;
        framepos += size;
    }
    crc = ffio_get_checksum(s->pb) ^ UINT32_MAX;
    if (crc != avio_rl32(s->pb) && s->error_recognition & AV_EF_CRCCHECK) {
        av_log(s, AV_LOG_ERROR, "Seek table CRC error\n");
        return AVERROR_INVALIDDATA;
    }

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id = AV_CODEC_ID_TTA;
    st->codecpar->channels = channels;
    st->codecpar->sample_rate = samplerate;
    st->codecpar->bits_per_coded_sample = bps;

    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
        int64_t pos = avio_tell(s->pb);
        ff_ape_parse_tag(s);
        avio_seek(s->pb, pos, SEEK_SET);
    }

    return 0;
}