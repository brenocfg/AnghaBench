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

__attribute__((used)) static int mmf_probe(const AVProbeData *p)
{
    /* check file header */
    if (p->buf[0] == 'M' && p->buf[1] == 'M' &&
        p->buf[2] == 'M' && p->buf[3] == 'D' &&
        p->buf[8] == 'C' && p->buf[9] == 'N' &&
        p->buf[10] == 'T' && p->buf[11] == 'I')
        return AVPROBE_SCORE_MAX;
    else
        return 0;
}