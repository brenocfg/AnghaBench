#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_prg; TYPE_1__* prg; } ;
struct TYPE_5__ {unsigned int id; scalar_t__ pmt_found; scalar_t__ nb_pids; } ;
typedef  TYPE_2__ MpegTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  clear_avprogram (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void clear_program(MpegTSContext *ts, unsigned int programid)
{
    int i;

    clear_avprogram(ts, programid);
    for (i = 0; i < ts->nb_prg; i++)
        if (ts->prg[i].id == programid) {
            ts->prg[i].nb_pids = 0;
            ts->prg[i].pmt_found = 0;
        }
}