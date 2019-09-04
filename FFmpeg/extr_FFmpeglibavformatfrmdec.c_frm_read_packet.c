#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {int /*<<< orphan*/  pb; TYPE_1__** streams; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int size; scalar_t__ stream_index; scalar_t__* data; } ;
struct TYPE_10__ {scalar_t__ count; } ;
struct TYPE_9__ {TYPE_5__* codecpar; } ;
typedef  TYPE_2__ FrmContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_PIX_FMT_BGRA ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int av_image_get_buffer_size (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int frm_read_packet(AVFormatContext *avctx, AVPacket *pkt)
{
    FrmContext *s = avctx->priv_data;
    AVCodecParameters *par = avctx->streams[0]->codecpar;
    int packet_size, ret;

    if (s->count)
        return AVERROR_EOF;

    packet_size = av_image_get_buffer_size(par->format, par->width, par->height, 1);
    if (packet_size < 0)
        return AVERROR_INVALIDDATA;

    ret = av_get_packet(avctx->pb, pkt, packet_size);
    if (ret < 0)
        return ret;

    if (par->format == AV_PIX_FMT_BGRA) {
        int i;
        for (i = 3; i + 1 <= pkt->size; i += 4)
            pkt->data[i] = 0xFF - pkt->data[i];
    }

    pkt->stream_index = 0;
    s->count++;

    return 0;
}