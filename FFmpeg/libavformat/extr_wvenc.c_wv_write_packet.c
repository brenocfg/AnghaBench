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
struct TYPE_9__ {int /*<<< orphan*/  samples; } ;
typedef  TYPE_1__ WvMuxContext ;
struct TYPE_10__ {scalar_t__ samples; } ;
typedef  TYPE_2__ WvHeader ;
struct TYPE_12__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_11__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ WV_HEADER_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int ff_wv_parse_header (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wv_write_packet(AVFormatContext *ctx, AVPacket *pkt)
{
    WvMuxContext *s = ctx->priv_data;
    WvHeader header;
    int ret;

    if (pkt->size < WV_HEADER_SIZE ||
        (ret = ff_wv_parse_header(&header, pkt->data)) < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid WavPack packet.\n");
        return AVERROR(EINVAL);
    }
    s->samples += header.samples;

    avio_write(ctx->pb, pkt->data, pkt->size);

    return 0;
}