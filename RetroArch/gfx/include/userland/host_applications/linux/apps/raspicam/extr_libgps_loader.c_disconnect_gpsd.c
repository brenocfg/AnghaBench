#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ gpsd_connected; int /*<<< orphan*/  gpsdata; int /*<<< orphan*/  (* gps_close ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* gps_stream ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * libgps_handle; } ;
typedef  TYPE_1__ gpsd_info ;

/* Variables and functions */
 int /*<<< orphan*/  WATCH_DISABLE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

int disconnect_gpsd(gpsd_info *gpsd)
{
   if (gpsd->libgps_handle == NULL)
      return -1;
   if (gpsd->gpsd_connected)
   {
      gpsd->gps_stream(&gpsd->gpsdata, WATCH_DISABLE, NULL);
      gpsd->gps_close(&gpsd->gpsdata);
      gpsd->gpsd_connected = 0;
   }
   return 0;
}