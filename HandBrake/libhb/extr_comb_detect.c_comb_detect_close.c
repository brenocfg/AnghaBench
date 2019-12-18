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
struct TYPE_5__ {int mode; scalar_t__ filter_mode; struct TYPE_5__* block_score; int /*<<< orphan*/  mask_temp; int /*<<< orphan*/  mask_filtered; int /*<<< orphan*/  mask; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * ref_used; int /*<<< orphan*/  mask_dilate_taskset; int /*<<< orphan*/  mask_erode_taskset; int /*<<< orphan*/  mask_filter_taskset; int /*<<< orphan*/  decomb_check_taskset; int /*<<< orphan*/  decomb_filter_taskset; int /*<<< orphan*/  frames; int /*<<< orphan*/  comb_none; int /*<<< orphan*/  comb_light; int /*<<< orphan*/  comb_heavy; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

/* Variables and functions */
 scalar_t__ FILTER_ERODE_DILATE ; 
 int MODE_FILTER ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskset_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void comb_detect_close( hb_filter_object_t * filter )
{
    hb_filter_private_t * pv = filter->private_data;

    if (pv == NULL)
    {
        return;
    }

    hb_log("comb detect: heavy %i | light %i | uncombed %i | total %i",
           pv->comb_heavy,  pv->comb_light,  pv->comb_none, pv->frames);

    taskset_fini( &pv->decomb_filter_taskset );
    taskset_fini( &pv->decomb_check_taskset );

    if (pv->mode & MODE_FILTER)
    {
        taskset_fini( &pv->mask_filter_taskset );
        if (pv->filter_mode == FILTER_ERODE_DILATE)
        {
            taskset_fini( &pv->mask_erode_taskset );
            taskset_fini( &pv->mask_dilate_taskset );
        }
    }

    /* Cleanup reference buffers. */
    int ii;
    for (ii = 0; ii < 3; ii++)
    {
        if (!pv->ref_used[ii])
        {
            hb_buffer_close(&pv->ref[ii]);
        }
    }

    /* Cleanup combing masks. */
    hb_buffer_close(&pv->mask);
    hb_buffer_close(&pv->mask_filtered);
    hb_buffer_close(&pv->mask_temp);

    free(pv->block_score);
    free( pv );
    filter->private_data = NULL;
}