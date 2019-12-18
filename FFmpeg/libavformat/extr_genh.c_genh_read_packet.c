#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ codec_id; int channels; int block_align; } ;
struct TYPE_13__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; TYPE_1__** streams; } ;
struct TYPE_12__ {scalar_t__ stream_index; void** data; } ;
struct TYPE_11__ {int dsp_int_type; int interleave_size; } ;
struct TYPE_10__ {TYPE_5__* codecpar; } ;
typedef  TYPE_2__ GENHDemuxContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ AV_CODEC_ID_ADPCM_THP ; 
 scalar_t__ AV_CODEC_ID_SDX2_DPCM ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int av_new_packet (TYPE_3__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 void* avio_r8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genh_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    GENHDemuxContext *c = s->priv_data;
    int ret;

    if (c->dsp_int_type == 1 && par->codec_id == AV_CODEC_ID_ADPCM_THP &&
        par->channels > 1) {
        int i, ch;

        if (avio_feof(s->pb))
            return AVERROR_EOF;
        ret = av_new_packet(pkt, 8 * par->channels);
        if (ret < 0)
            return ret;
        for (i = 0; i < 8 / c->interleave_size; i++) {
            for (ch = 0; ch < par->channels; ch++) {
                pkt->data[ch * 8 + i*c->interleave_size+0] = avio_r8(s->pb);
                pkt->data[ch * 8 + i*c->interleave_size+1] = avio_r8(s->pb);
            }
        }
        ret = 0;
    } else if (par->codec_id == AV_CODEC_ID_SDX2_DPCM) {
        ret = av_get_packet(s->pb, pkt, par->block_align * 1024);

    } else {
        ret = av_get_packet(s->pb, pkt, par->block_align ? par->block_align : 1024 * par->channels);
    }

    pkt->stream_index = 0;
    return ret;
}