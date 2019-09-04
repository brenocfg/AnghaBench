#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_12__ {int codec_id; int extradata_size; int codec_tag; int /*<<< orphan*/ * extradata; } ;
struct TYPE_11__ {int /*<<< orphan*/  pb; } ;
struct TYPE_10__ {TYPE_1__* internal; int /*<<< orphan*/  need_parsing; TYPE_4__* codecpar; } ;
struct TYPE_9__ {int /*<<< orphan*/  need_context_update; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_HEADERS ; 
 int AV_CODEC_ID_FLASHSV ; 
 int AV_CODEC_ID_FLASHSV2 ; 
 int AV_CODEC_ID_FLV1 ; 
 int AV_CODEC_ID_H263 ; 
 int AV_CODEC_ID_H264 ; 
 int AV_CODEC_ID_MPEG4 ; 
 int AV_CODEC_ID_VP6A ; 
 int AV_CODEC_ID_VP6F ; 
#define  FLV_CODECID_H263 135 
#define  FLV_CODECID_H264 134 
#define  FLV_CODECID_MPEG4 133 
#define  FLV_CODECID_REALH263 132 
#define  FLV_CODECID_SCREEN 131 
#define  FLV_CODECID_SCREEN2 130 
#define  FLV_CODECID_VP6 129 
#define  FLV_CODECID_VP6A 128 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  ff_alloc_extradata (TYPE_4__*,int) ; 

__attribute__((used)) static int flv_set_video_codec(AVFormatContext *s, AVStream *vstream,
                               int flv_codecid, int read)
{
    int ret = 0;
    AVCodecParameters *par = vstream->codecpar;
    enum AVCodecID old_codec_id = vstream->codecpar->codec_id;
    switch (flv_codecid) {
    case FLV_CODECID_H263:
        par->codec_id = AV_CODEC_ID_FLV1;
        break;
    case FLV_CODECID_REALH263:
        par->codec_id = AV_CODEC_ID_H263;
        break; // Really mean it this time
    case FLV_CODECID_SCREEN:
        par->codec_id = AV_CODEC_ID_FLASHSV;
        break;
    case FLV_CODECID_SCREEN2:
        par->codec_id = AV_CODEC_ID_FLASHSV2;
        break;
    case FLV_CODECID_VP6:
        par->codec_id = AV_CODEC_ID_VP6F;
    case FLV_CODECID_VP6A:
        if (flv_codecid == FLV_CODECID_VP6A)
            par->codec_id = AV_CODEC_ID_VP6A;
        if (read) {
            if (par->extradata_size != 1) {
                ff_alloc_extradata(par, 1);
            }
            if (par->extradata)
                par->extradata[0] = avio_r8(s->pb);
            else
                avio_skip(s->pb, 1);
        }
        ret = 1;     // 1 byte body size adjustment for flv_read_packet()
        break;
    case FLV_CODECID_H264:
        par->codec_id = AV_CODEC_ID_H264;
        vstream->need_parsing = AVSTREAM_PARSE_HEADERS;
        ret = 3;     // not 4, reading packet type will consume one byte
        break;
    case FLV_CODECID_MPEG4:
        par->codec_id = AV_CODEC_ID_MPEG4;
        ret = 3;
        break;
    default:
        avpriv_request_sample(s, "Video codec (%x)", flv_codecid);
        par->codec_tag = flv_codecid;
    }

    if (!vstream->internal->need_context_update && par->codec_id != old_codec_id) {
        avpriv_request_sample(s, "Changing the codec id midstream");
        return AVERROR_PATCHWELCOME;
    }

    return ret;
}