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
struct TYPE_3__ {char* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB16 (char*) ; 
 scalar_t__ AV_RN32 (char*) ; 

__attribute__((used)) static int ingenient_probe(const AVProbeData *p)
{
    if (   AV_RN32(p->buf) != AV_RN32("MJPG")
        || p->buf_size < 50
        || AV_RB16(p->buf + 48) != 0xffd8)
        return 0;
    return AVPROBE_SCORE_MAX * 3 / 4;
}