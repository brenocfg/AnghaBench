#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  mimetype ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_22__ {size_t nb_streams; TYPE_6__** asf_st; } ;
struct TYPE_21__ {int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
struct TYPE_20__ {int /*<<< orphan*/  pb; TYPE_7__* priv_data; } ;
struct TYPE_19__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {int /*<<< orphan*/  metadata; TYPE_4__ attached_pic; int /*<<< orphan*/  index; TYPE_1__* codecpar; int /*<<< orphan*/  disposition; } ;
struct TYPE_17__ {scalar_t__ id; int /*<<< orphan*/  str; } ;
struct TYPE_16__ {int codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ CodecMime ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ ASFStream ;
typedef  TYPE_7__ ASFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_DISPOSITION_ATTACHED_PIC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (char**) ; 
 scalar_t__ av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_malloc (int) ; 
 TYPE_6__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 TYPE_3__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_get_str16le (int /*<<< orphan*/ ,int,char*,int) ; 
 int avio_r8 (int /*<<< orphan*/ ) ; 
 int avio_rl32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_id3v2_mime_tags ; 
 char** ff_id3v2_picture_types ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int asf_read_picture(AVFormatContext *s, int len)
{
    ASFContext *asf       = s->priv_data;
    AVPacket pkt          = { 0 };
    const CodecMime *mime = ff_id3v2_mime_tags;
    enum  AVCodecID id    = AV_CODEC_ID_NONE;
    char mimetype[64];
    uint8_t  *desc = NULL;
    AVStream   *st = NULL;
    int ret, type, picsize, desc_len;
    ASFStream *asf_st;

    /* type + picsize + mime + desc */
    if (len < 1 + 4 + 2 + 2) {
        av_log(s, AV_LOG_ERROR, "Invalid attached picture size: %d.\n", len);
        return AVERROR_INVALIDDATA;
    }

    /* picture type */
    type = avio_r8(s->pb);
    len--;
    if (type >= FF_ARRAY_ELEMS(ff_id3v2_picture_types) || type < 0) {
        av_log(s, AV_LOG_WARNING, "Unknown attached picture type: %d.\n", type);
        type = 0;
    }

    /* picture data size */
    picsize = avio_rl32(s->pb);
    len    -= 4;

    /* picture MIME type */
    len -= avio_get_str16le(s->pb, len, mimetype, sizeof(mimetype));
    while (mime->id != AV_CODEC_ID_NONE) {
        if (!strncmp(mime->str, mimetype, sizeof(mimetype))) {
            id = mime->id;
            break;
        }
        mime++;
    }
    if (id == AV_CODEC_ID_NONE) {
        av_log(s, AV_LOG_ERROR, "Unknown attached picture mimetype: %s.\n",
               mimetype);
        return 0;
    }

    if (picsize >= len) {
        av_log(s, AV_LOG_ERROR, "Invalid attached picture data size: %d >= %d.\n",
               picsize, len);
        return AVERROR_INVALIDDATA;
    }

    /* picture description */
    desc_len = (len - picsize) * 2 + 1;
    desc     = av_malloc(desc_len);
    if (!desc)
        return AVERROR(ENOMEM);
    len -= avio_get_str16le(s->pb, len - picsize, desc, desc_len);

    ret = av_get_packet(s->pb, &pkt, picsize);
    if (ret < 0)
        goto fail;

    st  = avformat_new_stream(s, NULL);
    if (!st) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    asf->asf_st[asf->nb_streams] = av_mallocz(sizeof(*asf_st));
    asf_st = asf->asf_st[asf->nb_streams];
    if (!asf_st) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    st->disposition              |= AV_DISPOSITION_ATTACHED_PIC;
    st->codecpar->codec_type      = asf_st->type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id        = id;
    st->attached_pic              = pkt;
    st->attached_pic.stream_index = asf_st->index = st->index;
    st->attached_pic.flags       |= AV_PKT_FLAG_KEY;

    asf->nb_streams++;

    if (*desc) {
        if (av_dict_set(&st->metadata, "title", desc, AV_DICT_DONT_STRDUP_VAL) < 0)
            av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");
    } else
        av_freep(&desc);

    if (av_dict_set(&st->metadata, "comment", ff_id3v2_picture_types[type], 0) < 0)
        av_log(s, AV_LOG_WARNING, "av_dict_set failed.\n");

    return 0;

fail:
    av_freep(&desc);
    av_packet_unref(&pkt);
    return ret;
}