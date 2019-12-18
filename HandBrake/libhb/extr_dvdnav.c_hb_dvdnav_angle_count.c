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
 scalar_t__ DVDNAV_STATUS_OK ; 
 int /*<<< orphan*/  dvdnav_err_to_string (int /*<<< orphan*/ ) ; 
 scalar_t__ dvdnav_get_angle_info (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  hb_log (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hb_dvdnav_angle_count( hb_dvd_t * e )
{
    hb_dvdnav_t * d = &(e->dvdnav);
    int current, angle_count;

    if (dvdnav_get_angle_info( d->dvdnav, &current, &angle_count) != DVDNAV_STATUS_OK)
    {
        hb_log("dvdnav_get_angle_info %s", dvdnav_err_to_string(d->dvdnav));
        angle_count = 1;
    }
    return angle_count;
}