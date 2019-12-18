#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int title_count; struct TYPE_5__* path; scalar_t__ bd; scalar_t__ stream; struct TYPE_5__* title_info; } ;
typedef  TYPE_1__ hb_bd_t ;

/* Variables and functions */
 int /*<<< orphan*/  bd_close (scalar_t__) ; 
 int /*<<< orphan*/  bd_free_title_info (TYPE_1__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_stream_close (scalar_t__*) ; 

void hb_bd_close( hb_bd_t ** _d )
{
    hb_bd_t * d = *_d;
    int ii;

    if ( d->title_info )
    {
        for ( ii = 0; ii < d->title_count; ii++ )
            bd_free_title_info( d->title_info[ii] );
        free( d->title_info );
    }
    if( d->stream ) hb_stream_close( &d->stream );
    if( d->bd ) bd_close( d->bd );
    if( d->path ) free( d->path );

    free( d );
    *_d = NULL;
}