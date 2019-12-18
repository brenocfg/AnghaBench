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
typedef  int u8 ;
typedef  enum frontend_powerstate { ____Placeholder_frontend_powerstate } frontend_powerstate ;

/* Variables and functions */
 int FRONTEND_POWERSTATE_CHARGED ; 
 int FRONTEND_POWERSTATE_CHARGING ; 
 int FRONTEND_POWERSTATE_ON_POWER_SOURCE ; 
 int /*<<< orphan*/  PTMU_GetBatteryChargeState (int*) ; 
 int /*<<< orphan*/  mcuHwcGetBatteryLevel (int*) ; 

__attribute__((used)) static enum frontend_powerstate frontend_ctr_get_powerstate(
      int* seconds, int* percent)
{
   u8                 battery_percent = 0;
   u8                        charging = 0;

   mcuHwcGetBatteryLevel(&battery_percent);

   *percent                           = battery_percent;
   /* 3DS does not support seconds of charge remaining */
   *seconds                           = -1;

   PTMU_GetBatteryChargeState(&charging);

   if (charging)
   {
      if (battery_percent == 100)
         return FRONTEND_POWERSTATE_CHARGED;
      return FRONTEND_POWERSTATE_CHARGING;
   }

   return FRONTEND_POWERSTATE_ON_POWER_SOURCE;
}