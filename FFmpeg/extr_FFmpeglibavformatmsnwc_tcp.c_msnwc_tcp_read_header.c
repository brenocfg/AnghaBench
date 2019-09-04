#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_9__ {TYPE_3__* codecpar; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MIMIC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ HEADER_SIZE ; 
 int /*<<< orphan*/  MKTAG (char,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* avformat_new_stream (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int msnwc_tcp_read_header(AVFormatContext *ctx)
{
    AVIOContext *pb = ctx->pb;
    AVCodecParameters *par;
    AVStream *st;

    st = avformat_new_stream(ctx, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    par             = st->codecpar;
    par->codec_type = AVMEDIA_TYPE_VIDEO;
    par->codec_id   = AV_CODEC_ID_MIMIC;
    par->codec_tag  = MKTAG('M', 'L', '2', '0');

    avpriv_set_pts_info(st, 32, 1, 1000);

    /* Some files start with "connected\r\n\r\n".
     * So skip until we find the first byte of struct size */
    while(avio_r8(pb) != HEADER_SIZE && !avio_feof(pb)) ;

    if(avio_feof(pb)) {
        av_log(ctx, AV_LOG_ERROR, "Could not find valid start.\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}