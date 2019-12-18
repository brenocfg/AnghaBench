#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wps_st_cb_t ;
struct TYPE_2__ {int /*<<< orphan*/  st_cb; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int ESP_OK ; 
 TYPE_1__* gWpsSm ; 

int
wps_station_wps_register_cb(wps_st_cb_t cb)
{
    if (!gWpsSm) {
        return ESP_FAIL;
    }

    gWpsSm->st_cb = cb;
    return ESP_OK;
}