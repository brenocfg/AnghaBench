#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mclms_recent; int mclms_order; int num_channels; int* cdlms_ttl; int* transient; scalar_t__* transient_pos; int /*<<< orphan*/  samples_per_frame; TYPE_2__* channel; TYPE_1__** cdlms; } ;
typedef  TYPE_3__ WmallDecodeCtx ;
struct TYPE_6__ {int /*<<< orphan*/  transient_counter; } ;
struct TYPE_5__ {int /*<<< orphan*/  order; int /*<<< orphan*/  recent; } ;

/* Variables and functions */

__attribute__((used)) static void reset_codec(WmallDecodeCtx *s)
{
    int ich, ilms;
    s->mclms_recent = s->mclms_order * s->num_channels;
    for (ich = 0; ich < s->num_channels; ich++) {
        for (ilms = 0; ilms < s->cdlms_ttl[ich]; ilms++)
            s->cdlms[ich][ilms].recent = s->cdlms[ich][ilms].order;
        /* first sample of a seekable subframe is considered as the starting of
            a transient area which is samples_per_frame samples long */
        s->channel[ich].transient_counter = s->samples_per_frame;
        s->transient[ich]     = 1;
        s->transient_pos[ich] = 0;
    }
}