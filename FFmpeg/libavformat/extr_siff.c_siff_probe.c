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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RL32 (scalar_t__) ; 
 scalar_t__ TAG_SIFF ; 
 scalar_t__ TAG_SOUN ; 
 scalar_t__ TAG_VBV1 ; 

__attribute__((used)) static int siff_probe(const AVProbeData *p)
{
    uint32_t tag = AV_RL32(p->buf + 8);
    /* check file header */
    if (AV_RL32(p->buf) != TAG_SIFF ||
        (tag != TAG_VBV1 && tag != TAG_SOUN))
        return 0;
    return AVPROBE_SCORE_MAX;
}