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
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (scalar_t__) ; 
 int AV_RL32 (scalar_t__) ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    if (p->buf_size < 2096)
        return 0;
    if (   AV_RL32(p->buf     ) != 1
        || AV_RL32(p->buf +  8) > 100000
        || AV_RL32(p->buf + 12) > 8
        || AV_RL32(p->buf + 16) != 2096
        ||!AV_RL32(p->buf + 21)
        || AV_RL16(p->buf + 25) != 2096
        || AV_RL32(p->buf + 48) % AV_RL32(p->buf + 21)
        )
        return 0;
    return AVPROBE_SCORE_EXTENSION;
}