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
struct TYPE_13__ {int codec_tag; int channels; unsigned int sample_rate; scalar_t__ codec_id; } ;
struct TYPE_12__ {TYPE_2__* pb; TYPE_1__** streams; } ;
struct TYPE_11__ {int seekable; } ;
struct TYPE_10__ {TYPE_4__* codecpar; } ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ AV_CODEC_ID_ADPCM_IMA_WAV ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_wb16 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_3__*,char*) ; 

__attribute__((used)) static int rso_write_header(AVFormatContext *s)
{
    AVIOContext  *pb  = s->pb;
    AVCodecParameters *par = s->streams[0]->codecpar;

    if (!par->codec_tag)
        return AVERROR_INVALIDDATA;

    if (par->channels != 1) {
        av_log(s, AV_LOG_ERROR, "RSO only supports mono\n");
        return AVERROR_INVALIDDATA;
    }

    if (!(s->pb->seekable & AVIO_SEEKABLE_NORMAL)) {
        av_log(s, AV_LOG_ERROR, "muxer does not support non seekable output\n");
        return AVERROR_INVALIDDATA;
    }

    /* XXX: find legal sample rates (if any) */
    if (par->sample_rate >= 1u<<16) {
        av_log(s, AV_LOG_ERROR, "Sample rate must be < 65536\n");
        return AVERROR_INVALIDDATA;
    }

    if (par->codec_id == AV_CODEC_ID_ADPCM_IMA_WAV) {
        avpriv_report_missing_feature(s, "ADPCM in RSO");
        return AVERROR_PATCHWELCOME;
    }

    /* format header */
    avio_wb16(pb, par->codec_tag);   /* codec ID */
    avio_wb16(pb, 0);                /* data size, will be written at EOF */
    avio_wb16(pb, par->sample_rate);
    avio_wb16(pb, 0x0000);           /* play mode ? (0x0000 = don't loop) */

    avio_flush(pb);

    return 0;
}