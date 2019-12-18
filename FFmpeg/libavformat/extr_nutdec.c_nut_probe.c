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
struct TYPE_3__ {int buf_size; scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB32 (scalar_t__) ; 
 int MAIN_STARTCODE ; 

__attribute__((used)) static int nut_probe(const AVProbeData *p)
{
    int i;

    for (i = 0; i < p->buf_size-8; i++) {
        if (AV_RB32(p->buf+i) != MAIN_STARTCODE>>32)
            continue;
        if (AV_RB32(p->buf+i+4) == (MAIN_STARTCODE & 0xFFFFFFFF))
            return AVPROBE_SCORE_MAX;
    }
    return 0;
}