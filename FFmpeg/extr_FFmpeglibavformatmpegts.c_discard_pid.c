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
struct Program {int nb_pids; unsigned int* pids; scalar_t__ id; } ;
struct TYPE_7__ {int nb_prg; TYPE_2__* stream; struct Program* prg; } ;
struct TYPE_6__ {int nb_programs; TYPE_1__** programs; } ;
struct TYPE_5__ {scalar_t__ discard; scalar_t__ id; } ;
typedef  TYPE_3__ MpegTSContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 

__attribute__((used)) static int discard_pid(MpegTSContext *ts, unsigned int pid)
{
    int i, j, k;
    int used = 0, discarded = 0;
    struct Program *p;

    /* If none of the programs have .discard=AVDISCARD_ALL then there's
     * no way we have to discard this packet */
    for (k = 0; k < ts->stream->nb_programs; k++)
        if (ts->stream->programs[k]->discard == AVDISCARD_ALL)
            break;
    if (k == ts->stream->nb_programs)
        return 0;

    for (i = 0; i < ts->nb_prg; i++) {
        p = &ts->prg[i];
        for (j = 0; j < p->nb_pids; j++) {
            if (p->pids[j] != pid)
                continue;
            // is program with id p->id set to be discarded?
            for (k = 0; k < ts->stream->nb_programs; k++) {
                if (ts->stream->programs[k]->id == p->id) {
                    if (ts->stream->programs[k]->discard == AVDISCARD_ALL)
                        discarded++;
                    else
                        used++;
                }
            }
        }
    }

    return !used && discarded;
}