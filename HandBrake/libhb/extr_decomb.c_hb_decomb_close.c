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
struct TYPE_5__ {int mode; int post_processing; struct TYPE_5__* yadif_arguments; scalar_t__ tmpc; scalar_t__ cxy; scalar_t__ cy2; scalar_t__ cx2; int /*<<< orphan*/ * eedi_full; int /*<<< orphan*/ * eedi_half; int /*<<< orphan*/ * ref; int /*<<< orphan*/  eedi2_taskset; int /*<<< orphan*/  yadif_taskset; int /*<<< orphan*/  frames; int /*<<< orphan*/  unfiltered; int /*<<< orphan*/  blended; int /*<<< orphan*/  deinterlaced; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

/* Variables and functions */
 int MODE_DECOMB_EEDI2 ; 
 int /*<<< orphan*/  eedi2_aligned_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_buffer_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskset_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hb_decomb_close( hb_filter_object_t * filter )
{
    hb_filter_private_t * pv = filter->private_data;

    if( !pv )
    {
        return;
    }

    hb_log("decomb: deinterlaced %i | blended %i | unfiltered %i | total %i",
           pv->deinterlaced, pv->blended, pv->unfiltered, pv->frames);

    taskset_fini( &pv->yadif_taskset );

    if( pv->mode & MODE_DECOMB_EEDI2 )
    {
        taskset_fini( &pv->eedi2_taskset );
    }

    /* Cleanup reference buffers. */
    int ii;
    for (ii = 0; ii < 3; ii++)
    {
        hb_buffer_close(&pv->ref[ii]);
    }

    if( pv->mode & MODE_DECOMB_EEDI2 )
    {
        /* Cleanup eedi-half  buffers */
        int ii;
        for( ii = 0; ii < 4; ii++ )
        {
            hb_buffer_close(&pv->eedi_half[ii]);
        }

        /* Cleanup eedi-full  buffers */
        for( ii = 0; ii < 5; ii++ )
        {
            hb_buffer_close(&pv->eedi_full[ii]);
        }
    }

    if( pv->post_processing > 1  && ( pv->mode & MODE_DECOMB_EEDI2 ) )
    {
        if (pv->cx2) eedi2_aligned_free(pv->cx2);
        if (pv->cy2) eedi2_aligned_free(pv->cy2);
        if (pv->cxy) eedi2_aligned_free(pv->cxy);
        if (pv->tmpc) eedi2_aligned_free(pv->tmpc);
    }

    /*
     * free memory for yadif structs
     */
    free( pv->yadif_arguments );

    free( pv );
    filter->private_data = NULL;
}