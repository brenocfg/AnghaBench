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
struct TYPE_5__ {struct TYPE_5__* path; scalar_t__ reader; scalar_t__ vmg; } ;
typedef  TYPE_1__ hb_dvdread_t ;
struct TYPE_6__ {TYPE_1__ dvdread; } ;
typedef  TYPE_2__ hb_dvd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVDClose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ifoClose (scalar_t__) ; 

__attribute__((used)) static void hb_dvdread_close( hb_dvd_t ** _d )
{
    hb_dvdread_t * d = &((*_d)->dvdread);

    if( d->vmg )
    {
        ifoClose( d->vmg );
    }
    if( d->reader )
    {
        DVDClose( d->reader );
    }

    free( d->path );
    free( d );
    *_d = NULL;
}