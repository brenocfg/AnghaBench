#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int /*<<< orphan*/  pb; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int daud_write_packet(struct AVFormatContext *s, AVPacket *pkt)
{
    if (pkt->size > 65535) {
        av_log(s, AV_LOG_ERROR,
               "Packet size too large for s302m. (%d > 65535)\n", pkt->size);
        return -1;
    }
    avio_wb16(s->pb, pkt->size);
    avio_wb16(s->pb, 0x8010); // unknown
    avio_write(s->pb, pkt->data, pkt->size);
    return 0;
}