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
struct TYPE_6__ {unsigned int nb_streams; int nb_programs; TYPE_1__** programs; } ;
struct TYPE_5__ {int id; int nb_stream_indexes; unsigned int* stream_index; } ;
typedef  TYPE_1__ AVProgram ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 void* av_realloc_array (unsigned int*,int,int) ; 

void av_program_add_stream_index(AVFormatContext *ac, int progid, unsigned idx)
{
    int i, j;
    AVProgram *program = NULL;
    void *tmp;

    if (idx >= ac->nb_streams) {
        av_log(ac, AV_LOG_ERROR, "stream index %d is not valid\n", idx);
        return;
    }

    for (i = 0; i < ac->nb_programs; i++) {
        if (ac->programs[i]->id != progid)
            continue;
        program = ac->programs[i];
        for (j = 0; j < program->nb_stream_indexes; j++)
            if (program->stream_index[j] == idx)
                return;

        tmp = av_realloc_array(program->stream_index, program->nb_stream_indexes+1, sizeof(unsigned int));
        if (!tmp)
            return;
        program->stream_index = tmp;
        program->stream_index[program->nb_stream_indexes++] = idx;
        return;
    }
}