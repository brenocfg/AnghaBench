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
struct TYPE_3__ {int nb_units; int /*<<< orphan*/ * units; } ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  cbs_unit_uninit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int ff_cbs_delete_unit(CodedBitstreamContext *ctx,
                       CodedBitstreamFragment *frag,
                       int position)
{
    if (position < 0 || position >= frag->nb_units)
        return AVERROR(EINVAL);

    cbs_unit_uninit(ctx, &frag->units[position]);

    --frag->nb_units;

    if (frag->nb_units > 0)
        memmove(frag->units + position,
                frag->units + position + 1,
                (frag->nb_units - position) * sizeof(*frag->units));

    return 0;
}