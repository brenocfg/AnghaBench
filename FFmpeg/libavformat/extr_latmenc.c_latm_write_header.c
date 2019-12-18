#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ codec_id; scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
struct TYPE_8__ {TYPE_1__** streams; } ;
struct TYPE_7__ {TYPE_3__* codecpar; } ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_AAC_LATM ; 
 scalar_t__ AV_CODEC_ID_MP4ALS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ latm_decode_extradata (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int latm_write_header(AVFormatContext *s)
{
    AVCodecParameters *par = s->streams[0]->codecpar;

    if (par->codec_id == AV_CODEC_ID_AAC_LATM)
        return 0;
    if (par->codec_id != AV_CODEC_ID_AAC && par->codec_id != AV_CODEC_ID_MP4ALS) {
        av_log(s, AV_LOG_ERROR, "Only AAC, LATM and ALS are supported\n");
        return AVERROR(EINVAL);
    }

    if (par->extradata_size > 0 &&
        latm_decode_extradata(s, par->extradata, par->extradata_size) < 0)
        return AVERROR_INVALIDDATA;

    return 0;
}