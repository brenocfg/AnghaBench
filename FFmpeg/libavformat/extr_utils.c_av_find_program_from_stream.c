#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nb_programs; TYPE_1__** programs; } ;
struct TYPE_6__ {int nb_stream_indexes; int* stream_index; } ;
typedef  TYPE_1__ AVProgram ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */

AVProgram *av_find_program_from_stream(AVFormatContext *ic, AVProgram *last, int s)
{
    int i, j;

    for (i = 0; i < ic->nb_programs; i++) {
        if (ic->programs[i] == last) {
            last = NULL;
        } else {
            if (!last)
                for (j = 0; j < ic->programs[i]->nb_stream_indexes; j++)
                    if (ic->programs[i]->stream_index[j] == s)
                        return ic->programs[i];
        }
    }
    return NULL;
}