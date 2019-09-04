#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nb_refs; int /*<<< orphan*/ * used; } ;
struct TYPE_6__ {TYPE_3__ long_term_rps; TYPE_2__* short_term_rps; } ;
struct TYPE_9__ {TYPE_1__ sh; } ;
struct TYPE_7__ {int num_negative_pics; int num_delta_pocs; int /*<<< orphan*/ * used; } ;
typedef  TYPE_2__ ShortTermRPS ;
typedef  TYPE_3__ LongTermRPS ;
typedef  TYPE_4__ HEVCContext ;

/* Variables and functions */

int ff_hevc_frame_nb_refs(const HEVCContext *s)
{
    int ret = 0;
    int i;
    const ShortTermRPS *rps = s->sh.short_term_rps;
    const LongTermRPS *long_rps = &s->sh.long_term_rps;

    if (rps) {
        for (i = 0; i < rps->num_negative_pics; i++)
            ret += !!rps->used[i];
        for (; i < rps->num_delta_pocs; i++)
            ret += !!rps->used[i];
    }

    if (long_rps) {
        for (i = 0; i < long_rps->nb_refs; i++)
            ret += !!long_rps->used[i];
    }
    return ret;
}