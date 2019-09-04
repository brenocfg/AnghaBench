#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t nb_streams; TYPE_2__** streams; } ;
struct TYPE_10__ {size_t stream_index; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_ATTACHMENT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int check_packet(AVFormatContext *s, AVPacket *pkt)
{
    if (!pkt)
        return 0;

    if (pkt->stream_index < 0 || pkt->stream_index >= s->nb_streams) {
        av_log(s, AV_LOG_ERROR, "Invalid packet stream index: %d\n",
               pkt->stream_index);
        return AVERROR(EINVAL);
    }

    if (s->streams[pkt->stream_index]->codecpar->codec_type == AVMEDIA_TYPE_ATTACHMENT) {
        av_log(s, AV_LOG_ERROR, "Received a packet for an attachment stream.\n");
        return AVERROR(EINVAL);
    }

    return 0;
}