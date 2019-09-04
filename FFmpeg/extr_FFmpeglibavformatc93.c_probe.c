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
struct TYPE_3__ {int buf_size; scalar_t__* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL16 (scalar_t__*) ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    int i;
    int index = 1;
    if (p->buf_size < 16)
        return 0;
    for (i = 0; i < 16; i += 4) {
        if (AV_RL16(p->buf + i) != index || !p->buf[i + 2] || !p->buf[i + 3])
            return 0;
        index += p->buf[i + 2];
    }
    return AVPROBE_SCORE_MAX;
}