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
 int AV_RL16 (char*) ; 
 int AV_RL32 (char*) ; 
 int CC_UNINT ; 

__attribute__((used)) static int cine_read_probe(const AVProbeData *p)
{
    int HeaderSize;
    if (p->buf[0] == 'C' && p->buf[1] == 'I' &&  // Type
        (HeaderSize = AV_RL16(p->buf + 2)) >= 0x2C &&  // HeaderSize
        AV_RL16(p->buf + 4) <= CC_UNINT &&       // Compression
        AV_RL16(p->buf + 6) <= 1 &&              // Version
        AV_RL32(p->buf + 20) &&                  // ImageCount
        AV_RL32(p->buf + 24) >= HeaderSize &&    // OffImageHeader
        AV_RL32(p->buf + 28) >= HeaderSize &&    // OffSetup
        AV_RL32(p->buf + 32) >= HeaderSize)      // OffImageOffsets
        return AVPROBE_SCORE_MAX;
    return 0;
}