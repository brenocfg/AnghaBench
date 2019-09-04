#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_17__ {TYPE_5__** streams; int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_16__ {size_t stream_index; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  dts; } ;
struct TYPE_15__ {int index; TYPE_2__* codecpar; TYPE_3__* priv_data; } ;
struct TYPE_11__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_14__ {unsigned int nb_fields; TYPE_1__ time_base; } ;
struct TYPE_13__ {int media_type; int /*<<< orphan*/  pframes; int /*<<< orphan*/  bframes; int /*<<< orphan*/  iframes; } ;
struct TYPE_12__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_3__ GXFStreamContext ;
typedef  TYPE_4__ GXFContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_DVVIDEO ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 int AV_PICTURE_TYPE_B ; 
 int AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 unsigned int av_rescale_rnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,unsigned int) ; 
 int gxf_parse_mpeg_frame (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_media_preamble(AVFormatContext *s, AVPacket *pkt, int size)
{
    GXFContext *gxf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[pkt->stream_index];
    GXFStreamContext *sc = st->priv_data;
    unsigned field_nb;
    /* If the video is frame-encoded, the frame numbers shall be represented by
     * even field numbers.
     * see SMPTE360M-2004  6.4.2.1.3 Media field number */
    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        field_nb = gxf->nb_fields;
    } else {
        field_nb = av_rescale_rnd(pkt->dts, gxf->time_base.den,
                                  (int64_t)48000*gxf->time_base.num, AV_ROUND_UP);
    }

    avio_w8(pb, sc->media_type);
    avio_w8(pb, st->index);
    avio_wb32(pb, field_nb);
    if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        avio_wb16(pb, 0);
        avio_wb16(pb, size / 2);
    } else if (st->codecpar->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        int frame_type = gxf_parse_mpeg_frame(sc, pkt->data, pkt->size);
        if (frame_type == AV_PICTURE_TYPE_I) {
            avio_w8(pb, 0x0d);
            sc->iframes++;
        } else if (frame_type == AV_PICTURE_TYPE_B) {
            avio_w8(pb, 0x0f);
            sc->bframes++;
        } else {
            avio_w8(pb, 0x0e);
            sc->pframes++;
        }
        avio_wb24(pb, size);
    } else if (st->codecpar->codec_id == AV_CODEC_ID_DVVIDEO) {
        avio_w8(pb, size / 4096);
        avio_wb24(pb, 0);
    } else
        avio_wb32(pb, size);
    avio_wb32(pb, field_nb);
    avio_w8(pb, 1); /* flags */
    avio_w8(pb, 0); /* reserved */
    return 16;
}