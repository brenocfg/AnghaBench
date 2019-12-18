#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_23__ {TYPE_2__* internal; TYPE_5__* pb; TYPE_3__* priv_data; } ;
struct TYPE_22__ {int seekable; } ;
struct TYPE_21__ {TYPE_1__* codecpar; } ;
struct TYPE_20__ {int audio_size; int data_end; int data_size; } ;
struct TYPE_19__ {void* data_offset; } ;
struct TYPE_18__ {int channels; int sample_rate; int block_align; long long bit_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  channel_layout; } ;
typedef  TYPE_3__ DSFContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_DSD_LSBF_PLANAR ; 
 int /*<<< orphan*/  AV_CODEC_ID_DSD_MSBF_PLANAR ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int INT_MAX ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_4__* avformat_new_stream (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int avio_rl32 (TYPE_5__*) ; 
 int avio_rl64 (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_5__*,int) ; 
 void* avio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,long long) ; 
 int /*<<< orphan*/ * dsf_channel_layout ; 
 int /*<<< orphan*/  read_id3 (TYPE_6__*,int) ; 

__attribute__((used)) static int dsf_read_header(AVFormatContext *s)
{
    DSFContext *dsf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;
    uint64_t id3pos;
    unsigned int channel_type;

    avio_skip(pb, 4);
    if (avio_rl64(pb) != 28)
        return AVERROR_INVALIDDATA;

    /* create primary stream before any id3 coverart streams */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(pb, 8);
    id3pos = avio_rl64(pb);
    if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
        read_id3(s, id3pos);
        avio_seek(pb, 28, SEEK_SET);
    }

    /* fmt chunk */

    if (avio_rl32(pb) != MKTAG('f', 'm', 't', ' ') || avio_rl64(pb) != 52)
        return AVERROR_INVALIDDATA;

    if (avio_rl32(pb) != 1) {
        avpriv_request_sample(s, "unknown format version");
        return AVERROR_INVALIDDATA;
    }

    if (avio_rl32(pb)) {
        avpriv_request_sample(s, "unknown format id");
        return AVERROR_INVALIDDATA;
    }

    channel_type = avio_rl32(pb);
    if (channel_type < FF_ARRAY_ELEMS(dsf_channel_layout))
        st->codecpar->channel_layout = dsf_channel_layout[channel_type];
    if (!st->codecpar->channel_layout)
        avpriv_request_sample(s, "channel type %i", channel_type);

    st->codecpar->codec_type   = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channels     = avio_rl32(pb);
    st->codecpar->sample_rate  = avio_rl32(pb) / 8;

    if (st->codecpar->channels <= 0)
        return AVERROR_INVALIDDATA;

    switch(avio_rl32(pb)) {
    case 1: st->codecpar->codec_id = AV_CODEC_ID_DSD_LSBF_PLANAR; break;
    case 8: st->codecpar->codec_id = AV_CODEC_ID_DSD_MSBF_PLANAR; break;
    default:
        avpriv_request_sample(s, "unknown most significant bit");
        return AVERROR_INVALIDDATA;
    }

    dsf->audio_size = avio_rl64(pb) / 8 * st->codecpar->channels;
    st->codecpar->block_align = avio_rl32(pb);
    if (st->codecpar->block_align > INT_MAX / st->codecpar->channels) {
        avpriv_request_sample(s, "block_align overflow");
        return AVERROR_INVALIDDATA;
    }
    st->codecpar->block_align *= st->codecpar->channels;
    st->codecpar->bit_rate = st->codecpar->channels * st->codecpar->sample_rate * 8LL;
    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
    avio_skip(pb, 4);

    /* data chunk */

    dsf->data_end = avio_tell(pb);
    if (avio_rl32(pb) != MKTAG('d', 'a', 't', 'a'))
        return AVERROR_INVALIDDATA;
    dsf->data_size = avio_rl64(pb) - 12;
    dsf->data_end += dsf->data_size + 12;
    s->internal->data_offset = avio_tell(pb);

    return 0;
}