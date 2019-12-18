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
struct TYPE_5__ {scalar_t__ ssa; scalar_t__ renderer; scalar_t__ ssaTrack; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ass_free_track (scalar_t__) ; 
 int /*<<< orphan*/  ass_library_done (scalar_t__) ; 
 int /*<<< orphan*/  ass_renderer_done (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void ssa_close( hb_filter_object_t * filter )
{
    hb_filter_private_t * pv = filter->private_data;

    if( !pv )
    {
        return;
    }

    if ( pv->ssaTrack )
        ass_free_track( pv->ssaTrack );
    if ( pv->renderer )
        ass_renderer_done( pv->renderer );
    if ( pv->ssa )
        ass_library_done( pv->ssa );

    free( pv );
    filter->private_data = NULL;
}