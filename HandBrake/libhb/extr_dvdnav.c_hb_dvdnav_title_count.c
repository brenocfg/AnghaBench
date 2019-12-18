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
struct TYPE_4__ {int /*<<< orphan*/  dvdnav; } ;
typedef  TYPE_1__ hb_dvdnav_t ;
struct TYPE_5__ {TYPE_1__ dvdnav; } ;
typedef  TYPE_2__ hb_dvd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvdnav_get_number_of_titles (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int hb_dvdnav_title_count( hb_dvd_t * e )
{
    int titles = 0;
    hb_dvdnav_t * d = &(e->dvdnav);

    dvdnav_get_number_of_titles(d->dvdnav, &titles);
    return titles;
}