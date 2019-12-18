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
struct TYPE_2__ {int (* ssid_is_online ) (unsigned int) ;} ;

/* Variables and functions */
 int stub1 (unsigned int) ; 
 TYPE_1__* wifi_driver ; 

bool driver_wifi_ssid_is_online(unsigned i)
{
   return wifi_driver->ssid_is_online(i);
}