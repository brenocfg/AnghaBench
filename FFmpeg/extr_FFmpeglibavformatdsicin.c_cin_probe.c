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
struct TYPE_3__ {int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL32 (int*) ; 

__attribute__((used)) static int cin_probe(const AVProbeData *p)
{
    /* header starts with this special marker */
    if (AV_RL32(&p->buf[0]) != 0x55AA0000)
        return 0;

    /* for accuracy, check some header field values */
    if (AV_RL32(&p->buf[12]) != 22050 || p->buf[16] != 16 || p->buf[17] != 0)
        return 0;

    return AVPROBE_SCORE_MAX;
}