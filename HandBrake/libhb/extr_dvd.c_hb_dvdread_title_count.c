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
struct TYPE_8__ {TYPE_2__* vmg; } ;
typedef  TYPE_3__ hb_dvdread_t ;
struct TYPE_9__ {TYPE_3__ dvdread; } ;
typedef  TYPE_4__ hb_dvd_t ;
struct TYPE_7__ {TYPE_1__* tt_srpt; } ;
struct TYPE_6__ {int nr_of_srpts; } ;

/* Variables and functions */

__attribute__((used)) static int hb_dvdread_title_count( hb_dvd_t * e )
{
    hb_dvdread_t *d = &(e->dvdread);
    return d->vmg->tt_srpt->nr_of_srpts;
}