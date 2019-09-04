#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nb_units_allocated; int /*<<< orphan*/  units; } ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ *,TYPE_1__*) ; 

void ff_cbs_fragment_free(CodedBitstreamContext *ctx,
                          CodedBitstreamFragment *frag)
{
    ff_cbs_fragment_reset(ctx, frag);

    av_freep(&frag->units);
    frag->nb_units_allocated = 0;
}