#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VividasDemuxContext ;
struct TYPE_7__ {int extradata_size; int* extradata; void* sample_rate; void* channels; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; void* height; void* width; } ;
struct TYPE_5__ {void* den; void* num; } ;
struct TYPE_6__ {int id; TYPE_3__* codecpar; void* nb_frames; TYPE_1__ time_base; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_VORBIS ; 
 int /*<<< orphan*/  AV_CODEC_ID_VP6 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 unsigned int av_xiphlacing (int*,int) ; 
 TYPE_2__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avio_alloc_context (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 void* avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_alloc_extradata (TYPE_3__*,int) ; 
 int ffio_read_varlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int track_header(VividasDemuxContext *viv, AVFormatContext *s,  uint8_t *buf, int size)
{
    int i,j;
    int64_t off;
    int val_1;
    int num_video, num_audio;
    AVIOContext *pb;

    pb = avio_alloc_context(buf, size, 0, NULL, NULL, NULL, NULL);
    if (!pb)
        return AVERROR(ENOMEM);

    ffio_read_varlen(pb); // track_header_len
    avio_r8(pb); // '1'

    val_1 = ffio_read_varlen(pb);

    for (i=0;i<val_1;i++) {
        int c = avio_r8(pb);
        for (j=0;j<c;j++) {
            avio_r8(pb); // val_3
            avio_r8(pb); // val_4
        }
    }

    avio_r8(pb); // num_streams

    off = avio_tell(pb);
    off += ffio_read_varlen(pb); // val_5

    avio_r8(pb); // '2'
    num_video = avio_r8(pb);

    avio_seek(pb, off, SEEK_SET);
    if (num_video != 1)
        av_log(s, AV_LOG_WARNING, "number of video tracks %d is not 1\n", num_video);

    for (i = 0; i < num_video; i++) {
        AVStream *st = avformat_new_stream(s, NULL);

        st->id = i;

        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id = AV_CODEC_ID_VP6;

        off = avio_tell(pb);
        off += ffio_read_varlen(pb);
        avio_r8(pb); // '3'
        avio_r8(pb); // val_7
        st->time_base.num = avio_rl32(pb); // frame_time
        st->time_base.den = avio_rl32(pb); // time_base
        st->nb_frames = avio_rl32(pb); // n frames
        st->codecpar->width = avio_rl16(pb); // width
        st->codecpar->height = avio_rl16(pb); // height
        avio_r8(pb); // val_8
        avio_rl32(pb); // val_9

        avio_seek(pb, off, SEEK_SET);
    }

    off = avio_tell(pb);
    off += ffio_read_varlen(pb); // val_10
    avio_r8(pb); // '4'
    num_audio = avio_r8(pb);
    avio_seek(pb, off, SEEK_SET);

    if (num_audio != 1)
        av_log(s, AV_LOG_WARNING, "number of audio tracks %d is not 1\n", num_audio);

    for(i=0;i<num_audio;i++) {
        int q;
        AVStream *st = avformat_new_stream(s, NULL);

        st->id = num_video + i;

        st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        st->codecpar->codec_id = AV_CODEC_ID_VORBIS;

        off = avio_tell(pb);
        off += ffio_read_varlen(pb); // length
        avio_r8(pb); // '5'
        avio_r8(pb); //codec_id
        avio_rl16(pb); //codec_subid
        st->codecpar->channels = avio_rl16(pb); // channels
        st->codecpar->sample_rate = avio_rl32(pb); // sample_rate
        avio_seek(pb, 10, SEEK_CUR); // data_1
        q = avio_r8(pb);
        avio_seek(pb, q, SEEK_CUR); // data_2
        avio_r8(pb); // zeropad

        if (avio_tell(pb) < off) {
            int num_data;
            int xd_size = 0;
            int data_len[256];
            int offset = 1;
            uint8_t *p;
            ffio_read_varlen(pb); // val_13
            avio_r8(pb); // '19'
            ffio_read_varlen(pb); // len_3
            num_data = avio_r8(pb);
            for (j = 0; j < num_data; j++) {
                uint64_t len = ffio_read_varlen(pb);
                if (len > INT_MAX/2 - xd_size) {
                    av_free(pb);
                    return AVERROR_INVALIDDATA;
                }
                data_len[j] = len;
                xd_size += len;
            }

            st->codecpar->extradata_size = 64 + xd_size + xd_size / 255;
            if (ff_alloc_extradata(st->codecpar, st->codecpar->extradata_size)) {
                av_free(pb);
                return AVERROR(ENOMEM);
            }

            p = st->codecpar->extradata;
            p[0] = 2;

            for (j = 0; j < num_data - 1; j++) {
                unsigned delta = av_xiphlacing(&p[offset], data_len[j]);
                if (delta > data_len[j]) {
                    av_free(pb);
                    return AVERROR_INVALIDDATA;
                }
                offset += delta;
            }

            for (j = 0; j < num_data; j++) {
                int ret = avio_read(pb, &p[offset], data_len[j]);
                if (ret < data_len[j]) {
                    st->codecpar->extradata_size = 0;
                    av_freep(&st->codecpar->extradata);
                    break;
                }
                offset += data_len[j];
            }

            if (offset < st->codecpar->extradata_size)
                st->codecpar->extradata_size = offset;
        }
    }

    av_free(pb);
    return 0;
}