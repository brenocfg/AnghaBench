#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int transient; int blocks; scalar_t__ silence; } ;
struct TYPE_14__ {int framesize; } ;
struct TYPE_15__ {int redo_analysis; TYPE_1__ p; int /*<<< orphan*/ ** steps; } ;
typedef  int /*<<< orphan*/  OpusPsyStep ;
typedef  TYPE_2__ OpusPsyContext ;
typedef  TYPE_3__ CeltFrame ;

/* Variables and functions */
 int CELT_OVERLAP ; 
 int OPUS_BLOCK_SIZE (int) ; 
 int /*<<< orphan*/  celt_gauge_psy_weight (TYPE_2__*,int /*<<< orphan*/ **,TYPE_3__*) ; 
 int /*<<< orphan*/  celt_search_for_dual_stereo (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  celt_search_for_intensity (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  celt_search_for_tf (TYPE_2__*,int /*<<< orphan*/ **,TYPE_3__*) ; 

int ff_opus_psy_celt_frame_process(OpusPsyContext *s, CeltFrame *f, int index)
{
    int start_transient_flag = f->transient;
    OpusPsyStep **start = &s->steps[index * (1 << s->p.framesize)];

    if (f->silence)
        return 0;

    celt_gauge_psy_weight(s, start, f);
    celt_search_for_intensity(s, f);
    celt_search_for_dual_stereo(s, f);
    celt_search_for_tf(s, start, f);

    if (f->transient != start_transient_flag) {
        f->blocks = f->transient ? OPUS_BLOCK_SIZE(s->p.framesize)/CELT_OVERLAP : 1;
        s->redo_analysis = 1;
        return 1;
    }

    s->redo_analysis = 0;

    return 0;
}