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
typedef  enum wifi_driver_enum { ____Placeholder_wifi_driver_enum } wifi_driver_enum ;

/* Variables and functions */
#define  WIFI_CONNMANCTL 129 
 int WIFI_DEFAULT_DRIVER ; 
#define  WIFI_NULL 128 

const char *config_get_default_wifi(void)
{
   enum wifi_driver_enum default_driver = WIFI_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case WIFI_CONNMANCTL:
         return "connmanctl";
      case WIFI_NULL:
         break;
   }

   return "null";
}