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
struct TYPE_3__ {char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RB16 (char*) ; 
 int AV_RL16 (int*) ; 

__attribute__((used)) static int yop_probe(const AVProbeData *probe_packet)
{
    if (AV_RB16(probe_packet->buf) == AV_RB16("YO")  &&
        probe_packet->buf[2]<10                      &&
        probe_packet->buf[3]<10                      &&
        probe_packet->buf[6]                         &&
        probe_packet->buf[7]                         &&
        !(probe_packet->buf[8] & 1)                  &&
        !(probe_packet->buf[10] & 1)                 &&
        AV_RL16(probe_packet->buf + 12 + 6) >= 920    &&
        AV_RL16(probe_packet->buf + 12 + 6) < probe_packet->buf[12] * 3 + 4 + probe_packet->buf[7] * 2048
    )
        return AVPROBE_SCORE_MAX * 3 / 4;

    return 0;
}