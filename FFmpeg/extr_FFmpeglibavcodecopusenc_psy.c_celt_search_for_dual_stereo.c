#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dual_stereo; } ;
struct TYPE_9__ {int dual_stereo_used; TYPE_1__* avctx; } ;
struct TYPE_8__ {int channels; } ;
typedef  TYPE_2__ OpusPsyContext ;
typedef  TYPE_3__ CeltFrame ;

/* Variables and functions */
 int /*<<< orphan*/  bands_dist (TYPE_2__*,TYPE_3__*,float*) ; 

__attribute__((used)) static void celt_search_for_dual_stereo(OpusPsyContext *s, CeltFrame *f)
{
    float td1, td2;
    f->dual_stereo = 0;

    if (s->avctx->channels < 2)
        return;

    bands_dist(s, f, &td1);
    f->dual_stereo = 1;
    bands_dist(s, f, &td2);

    f->dual_stereo = td2 < td1;
    s->dual_stereo_used += td2 < td1;
}