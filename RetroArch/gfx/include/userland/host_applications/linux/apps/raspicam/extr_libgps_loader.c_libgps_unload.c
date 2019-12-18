#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * libgps_handle; } ;
typedef  TYPE_1__ gpsd_info ;

/* Variables and functions */
 int /*<<< orphan*/  disconnect_gpsd (TYPE_1__*) ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 

void libgps_unload(gpsd_info *gpsd)
{
   if (gpsd->libgps_handle)
   {
      disconnect_gpsd(gpsd);
      dlclose(gpsd->libgps_handle);
      gpsd->libgps_handle = NULL;
   }
}