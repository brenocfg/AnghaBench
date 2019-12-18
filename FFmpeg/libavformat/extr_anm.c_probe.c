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
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 scalar_t__ ANIM_TAG ; 
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RL16 (int /*<<< orphan*/ *) ; 
 scalar_t__ AV_RL32 (int /*<<< orphan*/ *) ; 
 scalar_t__ LPF_TAG ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    /* verify tags and video dimensions */
    if (AV_RL32(&p->buf[0])  == LPF_TAG &&
        AV_RL32(&p->buf[16]) == ANIM_TAG &&
        AV_RL16(&p->buf[20]) && AV_RL16(&p->buf[22]))
        return AVPROBE_SCORE_MAX;
    return 0;
}