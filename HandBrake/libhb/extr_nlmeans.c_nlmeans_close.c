#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* nframes; int threads; int max_frames; struct TYPE_7__* thread_data; struct TYPE_7__* frame; TYPE_1__* plane; int /*<<< orphan*/  taskset; } ;
typedef  TYPE_2__ hb_filter_private_t ;
struct TYPE_8__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_filter_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__* mem; TYPE_2__* mem_pre; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_lock_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskset_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nlmeans_close(hb_filter_object_t *filter)
{
    hb_filter_private_t *pv = filter->private_data;

    if (pv == NULL)
    {
        return;
    }

    taskset_fini(&pv->taskset);
    for (int c = 0; c < 3; c++)
    {
        for (int f = 0; f < pv->nframes[c]; f++)
        {
            if (pv->frame[f].plane[c].mem_pre != NULL &&
                pv->frame[f].plane[c].mem_pre != pv->frame[f].plane[c].mem)
            {
                free(pv->frame[f].plane[c].mem_pre);
                pv->frame[f].plane[c].mem_pre = NULL;
            }
            if (pv->frame[f].plane[c].mem != NULL)
            {
                free(pv->frame[f].plane[c].mem);
                pv->frame[f].plane[c].mem = NULL;
            }
        }
    }

    for (int ii = 0; ii < pv->threads + pv->max_frames; ii++)
    {
        for (int c = 0; c < 3; c++)
        {
            hb_lock_close(&pv->frame[ii].plane[c].mutex);
        }
    }

    free(pv->frame);
    free(pv->thread_data);
    free(pv);
    filter->private_data = NULL;
}