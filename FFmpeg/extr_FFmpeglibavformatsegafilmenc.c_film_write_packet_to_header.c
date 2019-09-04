#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_5__ {int pts; int duration; int index; int size; int /*<<< orphan*/  keyframe; scalar_t__ audio; } ;
typedef  TYPE_1__ FILMPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int film_write_packet_to_header(AVFormatContext *format_context, FILMPacket *pkt)
{
    AVIOContext *pb = format_context->pb;
    /* The bits in these two 32-bit integers contain info about the contents of this sample */
    int32_t info1 = 0;
    int32_t info2 = 0;

    if (pkt->audio) {
        /* Always the same, carries no more information than "this is audio" */
        info1 = 0xFFFFFFFF;
        info2 = 1;
    } else {
        info1 = pkt->pts;
        info2 = pkt->duration;
        /* The top bit being set indicates a key frame */
        if (!pkt->keyframe)
            info1 |= (1 << 31);
    }

    /* Write the 16-byte sample info packet to the STAB chunk in the header */
    avio_wb32(pb, pkt->index);
    avio_wb32(pb, pkt->size);
    avio_wb32(pb, info1);
    avio_wb32(pb, info2);

    return 0;
}