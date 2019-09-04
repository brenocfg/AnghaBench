#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ codec_type; } ;
struct TYPE_11__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_10__ {size_t stream_index; scalar_t__ duration; scalar_t__ pts; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_5__* codecpar; } ;
struct TYPE_8__ {int /*<<< orphan*/  duration; } ;
typedef  TYPE_1__ SMJPEGMuxContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SMJPEG_SNDD ; 
 int /*<<< orphan*/  SMJPEG_VIDD ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smjpeg_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    SMJPEGMuxContext *smc = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[pkt->stream_index];
    AVCodecParameters *par = st->codecpar;

    if (par->codec_type == AVMEDIA_TYPE_AUDIO)
        avio_wl32(pb, SMJPEG_SNDD);
    else if (par->codec_type == AVMEDIA_TYPE_VIDEO)
        avio_wl32(pb, SMJPEG_VIDD);
    else
        return 0;

    avio_wb32(pb, pkt->pts);
    avio_wb32(pb, pkt->size);
    avio_write(pb, pkt->data, pkt->size);

    smc->duration = FFMAX(smc->duration, pkt->pts + pkt->duration);
    return 0;
}