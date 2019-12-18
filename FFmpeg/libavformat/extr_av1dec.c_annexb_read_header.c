#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_20__ {TYPE_3__* priv_data; } ;
struct TYPE_19__ {TYPE_9__* codecpar; TYPE_2__* internal; int /*<<< orphan*/  need_parsing; } ;
struct TYPE_18__ {TYPE_11__* bsf; int /*<<< orphan*/  framerate; } ;
struct TYPE_17__ {TYPE_1__* avctx; } ;
struct TYPE_16__ {int /*<<< orphan*/  framerate; } ;
struct TYPE_15__ {int /*<<< orphan*/  par_in; } ;
typedef  TYPE_3__ AnnexBContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVBitStreamFilter ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_HEADERS ; 
 int /*<<< orphan*/  AV_CODEC_ID_AV1 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_bsf_alloc (int /*<<< orphan*/  const*,TYPE_11__**) ; 
 int /*<<< orphan*/  av_bsf_free (TYPE_11__**) ; 
 int /*<<< orphan*/ * av_bsf_get_by_name (char*) ; 
 int av_bsf_init (TYPE_11__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int avcodec_parameters_copy (int /*<<< orphan*/ ,TYPE_9__*) ; 
 TYPE_4__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int) ; 

__attribute__((used)) static int annexb_read_header(AVFormatContext *s)
{
    AnnexBContext *c = s->priv_data;
    const AVBitStreamFilter *filter = av_bsf_get_by_name("av1_frame_merge");
    AVStream *st;
    int ret;

    if (!filter) {
        av_log(c, AV_LOG_ERROR, "av1_frame_merge bitstream filter "
               "not found. This is a bug, please report it.\n");
        return AVERROR_BUG;
    }

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_AV1;
    st->need_parsing = AVSTREAM_PARSE_HEADERS;

    st->internal->avctx->framerate = c->framerate;
    // taken from rawvideo demuxers
    avpriv_set_pts_info(st, 64, 1, 1200000);

    ret = av_bsf_alloc(filter, &c->bsf);
    if (ret < 0)
        return ret;

    ret = avcodec_parameters_copy(c->bsf->par_in, st->codecpar);
    if (ret < 0) {
        av_bsf_free(&c->bsf);
        return ret;
    }

    ret = av_bsf_init(c->bsf);
    if (ret < 0)
        av_bsf_free(&c->bsf);

    return ret;
}