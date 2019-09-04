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
typedef  int uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_13__ {scalar_t__ codec_id; scalar_t__ codec_type; int codec_tag; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_12__ {TYPE_2__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_11__ {int flags; TYPE_1__* audio_par; } ;
struct TYPE_10__ {int channels; scalar_t__ sample_rate; int profile; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ FLVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FLV_AAC_SEQ_HEADER_DETECT ; 
 int FLV_FRAME_KEY ; 
 int FLV_TAG_TYPE_AUDIO ; 
 int FLV_TAG_TYPE_VIDEO ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_isom_write_avcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int get_audio_flags (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__* mpeg4audio_sample_rates ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_timestamp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void flv_write_codec_header(AVFormatContext* s, AVCodecParameters* par, int64_t ts) {
    int64_t data_size;
    AVIOContext *pb = s->pb;
    FLVContext *flv = s->priv_data;

    if (par->codec_id == AV_CODEC_ID_AAC || par->codec_id == AV_CODEC_ID_H264
            || par->codec_id == AV_CODEC_ID_MPEG4) {
        int64_t pos;
        avio_w8(pb,
                par->codec_type == AVMEDIA_TYPE_VIDEO ?
                        FLV_TAG_TYPE_VIDEO : FLV_TAG_TYPE_AUDIO);
        avio_wb24(pb, 0); // size patched later
        put_timestamp(pb, ts);
        avio_wb24(pb, 0); // streamid
        pos = avio_tell(pb);
        if (par->codec_id == AV_CODEC_ID_AAC) {
            avio_w8(pb, get_audio_flags(s, par));
            avio_w8(pb, 0); // AAC sequence header

            if (!par->extradata_size && (flv->flags & FLV_AAC_SEQ_HEADER_DETECT)) {
                PutBitContext pbc;
                int samplerate_index;
                int channels = flv->audio_par->channels
                        - (flv->audio_par->channels == 8 ? 1 : 0);
                uint8_t data[2];

                for (samplerate_index = 0; samplerate_index < 16;
                        samplerate_index++)
                    if (flv->audio_par->sample_rate
                            == mpeg4audio_sample_rates[samplerate_index])
                        break;

                init_put_bits(&pbc, data, sizeof(data));
                put_bits(&pbc, 5, flv->audio_par->profile + 1); //profile
                put_bits(&pbc, 4, samplerate_index); //sample rate index
                put_bits(&pbc, 4, channels);
                put_bits(&pbc, 1, 0); //frame length - 1024 samples
                put_bits(&pbc, 1, 0); //does not depend on core coder
                put_bits(&pbc, 1, 0); //is not extension
                flush_put_bits(&pbc);

                avio_w8(pb, data[0]);
                avio_w8(pb, data[1]);

                av_log(s, AV_LOG_WARNING, "AAC sequence header: %02x %02x.\n",
                        data[0], data[1]);
            }
            avio_write(pb, par->extradata, par->extradata_size);
        } else {
            avio_w8(pb, par->codec_tag | FLV_FRAME_KEY); // flags
            avio_w8(pb, 0); // AVC sequence header
            avio_wb24(pb, 0); // composition time
            ff_isom_write_avcc(pb, par->extradata, par->extradata_size);
        }
        data_size = avio_tell(pb) - pos;
        avio_seek(pb, -data_size - 10, SEEK_CUR);
        avio_wb24(pb, data_size);
        avio_skip(pb, data_size + 10 - 3);
        avio_wb32(pb, data_size + 11); // previous tag size
    }
}