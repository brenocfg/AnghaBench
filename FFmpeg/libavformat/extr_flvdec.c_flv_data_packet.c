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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_13__ {int nb_streams; int /*<<< orphan*/ * pb; TYPE_2__** streams; } ;
struct TYPE_12__ {int dts; int pts; int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; } ;
struct TYPE_11__ {int /*<<< orphan*/  index; TYPE_1__* codecpar; } ;
struct TYPE_10__ {scalar_t__ codec_type; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  scalar_t__ AMFDataType ;

/* Variables and functions */
#define  AMF_DATA_TYPE_ARRAY 130 
#define  AMF_DATA_TYPE_MIXEDARRAY 129 
#define  AMF_DATA_TYPE_OBJECT 128 
 scalar_t__ AMF_DATA_TYPE_STRING ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_CODEC_ID_TEXT ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int amf_get_string (int /*<<< orphan*/ *,char*,int) ; 
 int amf_skip_tag (int /*<<< orphan*/ *,scalar_t__) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* create_stream (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int flv_data_packet(AVFormatContext *s, AVPacket *pkt,
                           int64_t dts, int64_t next)
{
    AVIOContext *pb = s->pb;
    AVStream *st    = NULL;
    char buf[20];
    int ret = AVERROR_INVALIDDATA;
    int i, length = -1;
    int array = 0;

    switch (avio_r8(pb)) {
    case AMF_DATA_TYPE_ARRAY:
        array = 1;
    case AMF_DATA_TYPE_MIXEDARRAY:
        avio_seek(pb, 4, SEEK_CUR);
    case AMF_DATA_TYPE_OBJECT:
        break;
    default:
        goto skip;
    }

    while (array || (ret = amf_get_string(pb, buf, sizeof(buf))) > 0) {
        AMFDataType type = avio_r8(pb);
        if (type == AMF_DATA_TYPE_STRING && (array || !strcmp(buf, "text"))) {
            length = avio_rb16(pb);
            ret    = av_get_packet(pb, pkt, length);
            if (ret < 0)
                goto skip;
            else
                break;
        } else {
            if ((ret = amf_skip_tag(pb, type)) < 0)
                goto skip;
        }
    }

    if (length < 0) {
        ret = AVERROR_INVALIDDATA;
        goto skip;
    }

    for (i = 0; i < s->nb_streams; i++) {
        st = s->streams[i];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE)
            break;
    }

    if (i == s->nb_streams) {
        st = create_stream(s, AVMEDIA_TYPE_SUBTITLE);
        if (!st)
            return AVERROR(ENOMEM);
        st->codecpar->codec_id = AV_CODEC_ID_TEXT;
    }

    pkt->dts  = dts;
    pkt->pts  = dts;
    pkt->size = ret;

    pkt->stream_index = st->index;
    pkt->flags       |= AV_PKT_FLAG_KEY;

skip:
    avio_seek(s->pb, next + 4, SEEK_SET);

    return ret;
}