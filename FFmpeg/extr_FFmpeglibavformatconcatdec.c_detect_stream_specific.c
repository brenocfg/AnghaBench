#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ codec_id; int extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_18__ {TYPE_8__* par_out; TYPE_8__* par_in; } ;
struct TYPE_17__ {TYPE_4__** streams; TYPE_3__* priv_data; } ;
struct TYPE_16__ {TYPE_8__* codecpar; } ;
struct TYPE_15__ {TYPE_5__* avf; scalar_t__ auto_convert; TYPE_1__* cur_file; } ;
struct TYPE_14__ {TYPE_6__* bsf; } ;
struct TYPE_13__ {TYPE_2__* streams; } ;
typedef  TYPE_2__ ConcatStream ;
typedef  TYPE_3__ ConcatContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVBitStreamFilter ;
typedef  TYPE_6__ AVBSFContext ;

/* Variables and functions */
 int AVERROR_BSF_NOT_FOUND ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int AV_RB24 (int /*<<< orphan*/ ) ; 
 int AV_RB32 (int /*<<< orphan*/ ) ; 
 int av_bsf_alloc (int /*<<< orphan*/  const*,TYPE_6__**) ; 
 int /*<<< orphan*/ * av_bsf_get_by_name (char*) ; 
 int av_bsf_init (TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int avcodec_parameters_copy (TYPE_8__*,TYPE_8__*) ; 

__attribute__((used)) static int detect_stream_specific(AVFormatContext *avf, int idx)
{
    ConcatContext *cat = avf->priv_data;
    AVStream *st = cat->avf->streams[idx];
    ConcatStream *cs = &cat->cur_file->streams[idx];
    const AVBitStreamFilter *filter;
    AVBSFContext *bsf;
    int ret;

    if (cat->auto_convert && st->codecpar->codec_id == AV_CODEC_ID_H264) {
        if (!st->codecpar->extradata_size                                                ||
            (st->codecpar->extradata_size >= 3 && AV_RB24(st->codecpar->extradata) == 1) ||
            (st->codecpar->extradata_size >= 4 && AV_RB32(st->codecpar->extradata) == 1))
            return 0;
        av_log(cat->avf, AV_LOG_INFO,
               "Auto-inserting h264_mp4toannexb bitstream filter\n");
        filter = av_bsf_get_by_name("h264_mp4toannexb");
        if (!filter) {
            av_log(avf, AV_LOG_ERROR, "h264_mp4toannexb bitstream filter "
                   "required for H.264 streams\n");
            return AVERROR_BSF_NOT_FOUND;
        }
        ret = av_bsf_alloc(filter, &bsf);
        if (ret < 0)
            return ret;
        cs->bsf = bsf;

        ret = avcodec_parameters_copy(bsf->par_in, st->codecpar);
        if (ret < 0)
           return ret;

        ret = av_bsf_init(bsf);
        if (ret < 0)
            return ret;

        ret = avcodec_parameters_copy(st->codecpar, bsf->par_out);
        if (ret < 0)
            return ret;
    }
    return 0;
}