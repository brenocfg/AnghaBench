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
typedef  enum location_driver_enum { ____Placeholder_location_driver_enum } location_driver_enum ;

/* Variables and functions */
#define  LOCATION_ANDROID 130 
#define  LOCATION_CORELOCATION 129 
 int LOCATION_DEFAULT_DRIVER ; 
#define  LOCATION_NULL 128 

const char *config_get_default_location(void)
{
   enum location_driver_enum default_driver = LOCATION_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case LOCATION_ANDROID:
         return "android";
      case LOCATION_CORELOCATION:
         return "corelocation";
      case LOCATION_NULL:
         break;
   }

   return "null";
}