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
struct Program {unsigned int id; } ;
struct TYPE_3__ {int nb_prg; struct Program* prg; } ;
typedef  TYPE_1__ MpegTSContext ;

/* Variables and functions */

__attribute__((used)) static struct Program * get_program(MpegTSContext *ts, unsigned int programid)
{
    int i;
    for (i = 0; i < ts->nb_prg; i++) {
        if (ts->prg[i].id == programid) {
            return &ts->prg[i];
        }
    }
    return NULL;
}