#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
typedef  enum TAKMetaDataType { ____Placeholder_TAKMetaDataType } TAKMetaDataType ;
struct TYPE_30__ {int error_recognition; TYPE_5__* pb; TYPE_3__* priv_data; } ;
struct TYPE_29__ {int seekable; } ;
struct TYPE_28__ {scalar_t__ duration; TYPE_1__* codecpar; scalar_t__ start_time; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_27__ {int mlast_frame; scalar_t__ data_end; } ;
struct TYPE_26__ {scalar_t__ samples; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; scalar_t__ ch_layout; int /*<<< orphan*/  bps; } ;
struct TYPE_25__ {int* extradata; int extradata_size; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; scalar_t__ channel_layout; int /*<<< orphan*/  bits_per_coded_sample; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ TAKStreamInfo ;
typedef  TYPE_3__ TAKDemuxContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL_RAW ; 
 int /*<<< orphan*/  AV_CODEC_ID_TAK ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TAK_ENCODER_VERSION_BITS ; 
 int /*<<< orphan*/  TAK_LAST_FRAME_POS_BITS ; 
 int /*<<< orphan*/  TAK_LAST_FRAME_SIZE_BITS ; 
#define  TAK_METADATA_ENCODER 132 
#define  TAK_METADATA_END 131 
#define  TAK_METADATA_LAST_FRAME 130 
#define  TAK_METADATA_MD5 129 
#define  TAK_METADATA_STREAMINFO 128 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_malloc (int /*<<< orphan*/ ) ; 
 TYPE_4__* avformat_new_stream (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_feof (TYPE_5__*) ; 
 int avio_r8 (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_rb24 (TYPE_5__*) ; 
 int avio_read (TYPE_5__*,int*,int) ; 
 int avio_rl24 (TYPE_5__*) ; 
 scalar_t__ avio_rl32 (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int avio_skip (TYPE_5__*,int) ; 
 int avio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int avpriv_tak_parse_streaminfo (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  ff_ape_parse_tag (TYPE_6__*) ; 
 int /*<<< orphan*/  ffio_get_checksum (TYPE_5__*) ; 
 int /*<<< orphan*/  ffio_init_checksum (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bits64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_bits_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_get_bits8 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tak_check_crc ; 

__attribute__((used)) static int tak_read_header(AVFormatContext *s)
{
    TAKDemuxContext *tc = s->priv_data;
    AVIOContext *pb     = s->pb;
    GetBitContext gb;
    AVStream *st;
    uint8_t *buffer = NULL;
    int ret;

    st = avformat_new_stream(s, 0);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->codec_id   = AV_CODEC_ID_TAK;
    st->need_parsing         = AVSTREAM_PARSE_FULL_RAW;

    tc->mlast_frame = 0;
    if (avio_rl32(pb) != MKTAG('t', 'B', 'a', 'K')) {
        avio_seek(pb, -4, SEEK_CUR);
        return 0;
    }

    while (!avio_feof(pb)) {
        enum TAKMetaDataType type;
        int size;

        type = avio_r8(pb) & 0x7f;
        size = avio_rl24(pb);

        switch (type) {
        case TAK_METADATA_STREAMINFO:
            if (st->codecpar->extradata)
                return AVERROR_INVALIDDATA;
        case TAK_METADATA_LAST_FRAME:
        case TAK_METADATA_ENCODER:
            if (size <= 3)
                return AVERROR_INVALIDDATA;

            buffer = av_malloc(size - 3 + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!buffer)
                return AVERROR(ENOMEM);
            memset(buffer + size - 3, 0, AV_INPUT_BUFFER_PADDING_SIZE);

            ffio_init_checksum(pb, tak_check_crc, 0xCE04B7U);
            if (avio_read(pb, buffer, size - 3) != size - 3) {
                av_freep(&buffer);
                return AVERROR(EIO);
            }
            if (ffio_get_checksum(s->pb) != avio_rb24(pb)) {
                av_log(s, AV_LOG_ERROR, "%d metadata block CRC error.\n", type);
                if (s->error_recognition & AV_EF_EXPLODE) {
                    av_freep(&buffer);
                    return AVERROR_INVALIDDATA;
                }
            }

            break;
        case TAK_METADATA_MD5: {
            uint8_t md5[16];
            int i;

            if (size != 19)
                return AVERROR_INVALIDDATA;
            ffio_init_checksum(pb, tak_check_crc, 0xCE04B7U);
            avio_read(pb, md5, 16);
            if (ffio_get_checksum(s->pb) != avio_rb24(pb)) {
                av_log(s, AV_LOG_ERROR, "MD5 metadata block CRC error.\n");
                if (s->error_recognition & AV_EF_EXPLODE)
                    return AVERROR_INVALIDDATA;
            }

            av_log(s, AV_LOG_VERBOSE, "MD5=");
            for (i = 0; i < 16; i++)
                av_log(s, AV_LOG_VERBOSE, "%02x", md5[i]);
            av_log(s, AV_LOG_VERBOSE, "\n");
            break;
        }
        case TAK_METADATA_END: {
            int64_t curpos = avio_tell(pb);

            if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
                ff_ape_parse_tag(s);
                avio_seek(pb, curpos, SEEK_SET);
            }

            tc->data_end += curpos;
            return 0;
        }
        default:
            ret = avio_skip(pb, size);
            if (ret < 0)
                return ret;
        }

        if (type == TAK_METADATA_STREAMINFO) {
            TAKStreamInfo ti;

            ret = avpriv_tak_parse_streaminfo(&ti, buffer, size -3);
            if (ret < 0)
                goto end;
            if (ti.samples > 0)
                st->duration = ti.samples;
            st->codecpar->bits_per_coded_sample = ti.bps;
            if (ti.ch_layout)
                st->codecpar->channel_layout = ti.ch_layout;
            st->codecpar->sample_rate           = ti.sample_rate;
            st->codecpar->channels              = ti.channels;
            st->start_time                   = 0;
            avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);
            st->codecpar->extradata             = buffer;
            st->codecpar->extradata_size        = size - 3;
            buffer                           = NULL;
        } else if (type == TAK_METADATA_LAST_FRAME) {
            if (size != 11) {
                ret = AVERROR_INVALIDDATA;
                goto end;
            }
            init_get_bits8(&gb, buffer, size - 3);
            tc->mlast_frame = 1;
            tc->data_end    = get_bits64(&gb, TAK_LAST_FRAME_POS_BITS) +
                              get_bits(&gb, TAK_LAST_FRAME_SIZE_BITS);
            av_freep(&buffer);
        } else if (type == TAK_METADATA_ENCODER) {
            init_get_bits8(&gb, buffer, size - 3);
            av_log(s, AV_LOG_VERBOSE, "encoder version: %0X\n",
                   get_bits_long(&gb, TAK_ENCODER_VERSION_BITS));
            av_freep(&buffer);
        }
    }

    return AVERROR_EOF;
end:
    av_freep(&buffer);
    return ret;
}