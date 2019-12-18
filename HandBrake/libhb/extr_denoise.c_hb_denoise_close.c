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
struct TYPE_5__ {struct TYPE_5__** hqdn3d_frame; struct TYPE_5__* hqdn3d_line; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void hb_denoise_close( hb_filter_object_t * filter )
{
    hb_filter_private_t * pv = filter->private_data;

    if( !pv )
    {
        return;
    }

	if( pv->hqdn3d_line )
    {
        free( pv->hqdn3d_line );
        pv->hqdn3d_line = NULL;
    }
	if( pv->hqdn3d_frame[0] )
    {
        free( pv->hqdn3d_frame[0] );
        pv->hqdn3d_frame[0] = NULL;
    }
	if( pv->hqdn3d_frame[1] )
    {
        free( pv->hqdn3d_frame[1] );
        pv->hqdn3d_frame[1] = NULL;
    }
	if( pv->hqdn3d_frame[2] )
    {
        free( pv->hqdn3d_frame[2] );
        pv->hqdn3d_frame[2] = NULL;
    }

    free( pv );
    filter->private_data = NULL;
}