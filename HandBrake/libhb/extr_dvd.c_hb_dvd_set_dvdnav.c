#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  dvd_methods ; 
 int /*<<< orphan*/  hb_dvdnav_methods () ; 
 int /*<<< orphan*/  hb_dvdread_methods () ; 

void hb_dvd_set_dvdnav( int enable )
{
    if (enable)
        dvd_methods = hb_dvdnav_methods();
    else
        dvd_methods = hb_dvdread_methods();
}