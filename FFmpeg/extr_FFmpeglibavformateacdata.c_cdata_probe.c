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
typedef  int uint8_t ;
struct TYPE_3__ {int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 

__attribute__((used)) static int cdata_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;

    if (b[0] == 0x04 && (b[1] == 0x00 || b[1] == 0x04 || b[1] == 0x0C || b[1] == 0x14))
        return AVPROBE_SCORE_MAX/8;
    return 0;
}