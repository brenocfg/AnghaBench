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
struct TYPE_3__ {int gpsd_connected; scalar_t__ (* gps_open ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  gpsdata; int /*<<< orphan*/  (* gps_stream ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  port; int /*<<< orphan*/  server; int /*<<< orphan*/ * libgps_handle; } ;
typedef  TYPE_1__ gpsd_info ;

/* Variables and functions */
 int /*<<< orphan*/  WATCH_ENABLE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int connect_gpsd(gpsd_info *gpsd)
{
   if (gpsd->libgps_handle == NULL)
      return -1;
   if (!gpsd->gpsd_connected)
   {
      if (gpsd->gps_open(gpsd->server, gpsd->port, &gpsd->gpsdata) != 0)
         return -1;
      gpsd->gpsd_connected = 1;
      gpsd->gps_stream(&gpsd->gpsdata, WATCH_ENABLE, NULL);
   }
   return 0;
}