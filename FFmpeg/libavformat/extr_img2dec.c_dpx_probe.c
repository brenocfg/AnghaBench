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
typedef  char uint8_t ;
struct TYPE_3__ {char* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB32 (char*) ; 
 int AV_RL32 (char*) ; 
 scalar_t__ AV_RN32 (char const*) ; 

__attribute__((used)) static int dpx_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;
    int w, h;
    int is_big = (AV_RN32(b) == AV_RN32("SDPX"));

    if (p->buf_size < 0x304+8)
        return 0;
    w = is_big ? AV_RB32(p->buf + 0x304) : AV_RL32(p->buf + 0x304);
    h = is_big ? AV_RB32(p->buf + 0x308) : AV_RL32(p->buf + 0x308);
    if (w <= 0 || h <= 0)
        return 0;

    if (is_big || AV_RN32(b) == AV_RN32("XPDS"))
        return AVPROBE_SCORE_EXTENSION + 1;
    return 0;
}