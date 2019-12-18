#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ next_frame; scalar_t__ max_frames; scalar_t__ threads; TYPE_2__** thread_data; TYPE_4__* frame; int /*<<< orphan*/  taskset; } ;
typedef  TYPE_3__ hb_filter_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_9__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int /*<<< orphan*/  out; } ;
struct TYPE_6__ {int /*<<< orphan*/ * mem; int /*<<< orphan*/ * mem_pre; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_4__ Frame ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskset_cycle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_buffer_t * nlmeans_filter(hb_filter_private_t *pv)
{
    if (pv->next_frame < pv->max_frames + pv->threads)
    {
        return NULL;
    }

    taskset_cycle(&pv->taskset);

    // Free buffers that are not needed for next taskset cycle
    for (int c = 0; c < 3; c++)
    {
        for (int t = 0; t < pv->threads; t++)
        {
            // Release last frame in buffer
            if (pv->frame[t].plane[c].mem_pre != NULL &&
                pv->frame[t].plane[c].mem_pre != pv->frame[t].plane[c].mem)
            {
                free(pv->frame[t].plane[c].mem_pre);
                pv->frame[t].plane[c].mem_pre = NULL;
            }
            if (pv->frame[t].plane[c].mem != NULL)
            {
                free(pv->frame[t].plane[c].mem);
                pv->frame[t].plane[c].mem = NULL;
            }
        }
    }
    // Shift frames in buffer down
    for (int f = 0; f < pv->max_frames; f++)
    {
        // Don't move the mutex!
        Frame frame = pv->frame[f];
        pv->frame[f] = pv->frame[f+pv->threads];
        for (int c = 0; c < 3; c++)
        {
            pv->frame[f].plane[c].mutex = frame.plane[c].mutex;
            pv->frame[f+pv->threads].plane[c].mem_pre = NULL;
            pv->frame[f+pv->threads].plane[c].mem = NULL;
        }
    }
    pv->next_frame -= pv->threads;

    // Collect results from taskset
    hb_buffer_list_t list;
    hb_buffer_list_clear(&list);
    for (int t = 0; t < pv->threads; t++)
    {
        hb_buffer_list_append(&list, pv->thread_data[t]->out);
    }
    return hb_buffer_list_clear(&list);
}