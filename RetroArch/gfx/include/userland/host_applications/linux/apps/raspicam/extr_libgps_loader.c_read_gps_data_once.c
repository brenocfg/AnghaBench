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
struct TYPE_3__ {int (* gps_read ) (int /*<<< orphan*/ *) ;scalar_t__ gpsd_connected; int /*<<< orphan*/  gpsdata; int /*<<< orphan*/  (* gps_close ) (int /*<<< orphan*/ *) ;scalar_t__ (* gps_waiting ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/ * libgps_handle; } ;
typedef  TYPE_1__ gpsd_info ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ *,int) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

int read_gps_data_once(gpsd_info *gpsd)
{
   if (gpsd->libgps_handle == NULL)
      return -1;
   if (gpsd->gpsd_connected)
   {
      if (gpsd->gps_waiting(&gpsd->gpsdata, 200))
      {
         int ret = gpsd->gps_read(&gpsd->gpsdata);
         if (ret < 0)
         {
            gpsd->gps_close(&gpsd->gpsdata);
            gpsd->gpsd_connected = 0;
            ret = 0;
         }
         return ret;
      }
   }
   return 0;
}