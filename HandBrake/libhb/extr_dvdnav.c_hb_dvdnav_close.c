#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* path; scalar_t__ reader; scalar_t__ vmg; scalar_t__ dvdnav; } ;
typedef  TYPE_1__ hb_dvdnav_t ;
struct TYPE_7__ {TYPE_1__ dvdnav; } ;
typedef  TYPE_2__ hb_dvd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVDClose (scalar_t__) ; 
 int /*<<< orphan*/  TitleCloseIfo (TYPE_1__*) ; 
 int /*<<< orphan*/  dvdnav_close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ifoClose (scalar_t__) ; 

__attribute__((used)) static void hb_dvdnav_close( hb_dvd_t ** _d )
{
    hb_dvdnav_t      * d = &((*_d)->dvdnav);

    if (d->dvdnav) dvdnav_close( d->dvdnav );
    if (d->vmg)    ifoClose( d->vmg );
    TitleCloseIfo(d);
    if (d->reader) DVDClose( d->reader );

    free(d->path);


    free( d );
    *_d = NULL;
}