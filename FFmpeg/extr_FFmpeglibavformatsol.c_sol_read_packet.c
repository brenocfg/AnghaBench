#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pb; } ;
struct TYPE_6__ {scalar_t__ stream_index; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  MAX_SIZE ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sol_read_packet(AVFormatContext *s,
                          AVPacket *pkt)
{
    int ret;

    if (avio_feof(s->pb))
        return AVERROR(EIO);
    ret= av_get_packet(s->pb, pkt, MAX_SIZE);
    if (ret < 0)
        return ret;
    pkt->flags &= ~AV_PKT_FLAG_CORRUPT;
    pkt->stream_index = 0;
    return 0;
}