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
struct TYPE_9__ {scalar_t__ codec_id; } ;
struct TYPE_8__ {int nb_streams; int /*<<< orphan*/ * pb; TYPE_1__** streams; } ;
struct TYPE_7__ {TYPE_3__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_WEBVTT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int webvtt_write_header(AVFormatContext *ctx)
{
    AVStream     *s = ctx->streams[0];
    AVCodecParameters *par = ctx->streams[0]->codecpar;
    AVIOContext *pb = ctx->pb;

    if (ctx->nb_streams != 1 || par->codec_id != AV_CODEC_ID_WEBVTT) {
        av_log(ctx, AV_LOG_ERROR, "Exactly one WebVTT stream is needed.\n");
        return AVERROR(EINVAL);
    }

    avpriv_set_pts_info(s, 64, 1, 1000);

    avio_printf(pb, "WEBVTT\n");
    avio_flush(pb);

    return 0;
}