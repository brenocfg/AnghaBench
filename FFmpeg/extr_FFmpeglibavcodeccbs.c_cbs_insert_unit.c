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
struct TYPE_3__ {int nb_units; int nb_units_allocated; int /*<<< orphan*/ * units; } ;
typedef  int /*<<< orphan*/  CodedBitstreamUnit ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc_array (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cbs_insert_unit(CodedBitstreamContext *ctx,
                           CodedBitstreamFragment *frag,
                           int position)
{
    CodedBitstreamUnit *units;

    if (frag->nb_units < frag->nb_units_allocated) {
        units = frag->units;

        if (position < frag->nb_units)
            memmove(units + position + 1, units + position,
                    (frag->nb_units - position) * sizeof(*units));
    } else {
        units = av_malloc_array(frag->nb_units + 1, sizeof(*units));
        if (!units)
            return AVERROR(ENOMEM);

        ++frag->nb_units_allocated;

        if (position > 0)
            memcpy(units, frag->units, position * sizeof(*units));

        if (position < frag->nb_units)
            memcpy(units + position + 1, frag->units + position,
                   (frag->nb_units - position) * sizeof(*units));
    }

    memset(units + position, 0, sizeof(*units));

    if (units != frag->units) {
        av_free(frag->units);
        frag->units = units;
    }

    ++frag->nb_units;

    return 0;
}