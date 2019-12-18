#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * file; int /*<<< orphan*/ * ifo; } ;
typedef  TYPE_1__ hb_dvdread_t ;
struct TYPE_5__ {TYPE_1__ dvdread; } ;
typedef  TYPE_2__ hb_dvd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVDCloseFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifoClose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hb_dvdread_stop( hb_dvd_t * e )
{
    hb_dvdread_t *d = &(e->dvdread);
    if( d->ifo )
    {
        ifoClose( d->ifo );
        d->ifo = NULL;
    }
    if( d->file )
    {
        DVDCloseFile( d->file );
        d->file = NULL;
    }
}