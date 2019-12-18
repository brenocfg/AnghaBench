#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  extradata; } ;
struct TYPE_14__ {TYPE_1__* internal; int /*<<< orphan*/  pb; } ;
struct TYPE_13__ {TYPE_4__* codecpar; } ;
struct TYPE_12__ {int /*<<< orphan*/  data_offset; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AVPRIV_CODEC2_EXTRADATA_SIZE ; 
 int /*<<< orphan*/  AVPRIV_CODEC2_HEADER_SIZE ; 
 scalar_t__ AVPRIV_CODEC2_MAGIC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int EXPECTED_CODEC2_MAJOR_VERSION ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rb24 (int /*<<< orphan*/ ) ; 
 int avpriv_codec2_version_from_extradata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_3__*,char*,int) ; 
 int codec2_read_header_common (TYPE_3__*,TYPE_2__*) ; 
 int ff_alloc_extradata (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ffio_read_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int codec2_read_header(AVFormatContext *s)
{
    AVStream *st = avformat_new_stream(s, NULL);
    int ret, version;

    if (!st) {
        return AVERROR(ENOMEM);
    }

    if (avio_rb24(s->pb) != AVPRIV_CODEC2_MAGIC) {
        av_log(s, AV_LOG_ERROR, "not a .c2 file\n");
        return AVERROR_INVALIDDATA;
    }

    ret = ff_alloc_extradata(st->codecpar, AVPRIV_CODEC2_EXTRADATA_SIZE);
    if (ret) {
        return ret;
    }

    ret = ffio_read_size(s->pb, st->codecpar->extradata, AVPRIV_CODEC2_EXTRADATA_SIZE);
    if (ret < 0) {
        return ret;
    }

    version = avpriv_codec2_version_from_extradata(st->codecpar->extradata);
    if ((version >> 8) != EXPECTED_CODEC2_MAJOR_VERSION) {
        avpriv_report_missing_feature(s, "Major version %i", version >> 8);
        return AVERROR_PATCHWELCOME;
    }

    s->internal->data_offset = AVPRIV_CODEC2_HEADER_SIZE;

    return codec2_read_header_common(s, st);
}