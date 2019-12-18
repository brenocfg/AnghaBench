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
struct TYPE_2__ {int /*<<< orphan*/  (* tether_start_stop ) (int,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,char*) ; 
 TYPE_1__* wifi_driver ; 

void driver_wifi_tether_start_stop(bool start, char* configfile)
{
   wifi_driver->tether_start_stop(start, configfile);
}