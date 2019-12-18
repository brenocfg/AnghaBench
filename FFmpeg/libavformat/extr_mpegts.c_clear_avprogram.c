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
struct TYPE_7__ {unsigned int id; scalar_t__ nb_stream_indexes; } ;
struct TYPE_6__ {TYPE_1__* stream; } ;
struct TYPE_5__ {int nb_programs; TYPE_3__** programs; } ;
typedef  TYPE_2__ MpegTSContext ;
typedef  TYPE_3__ AVProgram ;

/* Variables and functions */

__attribute__((used)) static void clear_avprogram(MpegTSContext *ts, unsigned int programid)
{
    AVProgram *prg = NULL;
    int i;

    for (i = 0; i < ts->stream->nb_programs; i++)
        if (ts->stream->programs[i]->id == programid) {
            prg = ts->stream->programs[i];
            break;
        }
    if (!prg)
        return;
    prg->nb_stream_indexes = 0;
}