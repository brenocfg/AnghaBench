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
struct TYPE_3__ {int stream_index; int flags; int duration; int dts; int pts; int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  HEXDUMP_PRINT (char*,...) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hex_dump_internal (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pkt_dump_internal(void *avcl, FILE *f, int level, const AVPacket *pkt,
                              int dump_payload, AVRational time_base)
{
    HEXDUMP_PRINT("stream #%d:\n", pkt->stream_index);
    HEXDUMP_PRINT("  keyframe=%d\n", (pkt->flags & AV_PKT_FLAG_KEY) != 0);
    HEXDUMP_PRINT("  duration=%0.3f\n", pkt->duration * av_q2d(time_base));
    /* DTS is _always_ valid after av_read_frame() */
    HEXDUMP_PRINT("  dts=");
    if (pkt->dts == AV_NOPTS_VALUE)
        HEXDUMP_PRINT("N/A");
    else
        HEXDUMP_PRINT("%0.3f", pkt->dts * av_q2d(time_base));
    /* PTS may not be known if B-frames are present. */
    HEXDUMP_PRINT("  pts=");
    if (pkt->pts == AV_NOPTS_VALUE)
        HEXDUMP_PRINT("N/A");
    else
        HEXDUMP_PRINT("%0.3f", pkt->pts * av_q2d(time_base));
    HEXDUMP_PRINT("\n");
    HEXDUMP_PRINT("  size=%d\n", pkt->size);
    if (dump_payload)
        hex_dump_internal(avcl, f, level, pkt->data, pkt->size);
}