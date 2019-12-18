#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* led_driver; } ;
struct TYPE_10__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* init ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,char*,TYPE_3__*) ; 
 TYPE_2__* config_get_ptr () ; 
 TYPE_3__* current_led_driver ; 
 TYPE_3__ null_led_driver ; 
 TYPE_3__ overlay_led_driver ; 
 TYPE_3__ rpi_led_driver ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 

bool led_driver_init(void)
{
   settings_t *settings = config_get_ptr();
   char *drivername     = settings ? settings->arrays.led_driver : NULL;

   if(!drivername)
      drivername = (char*)"null";

   current_led_driver = &null_led_driver;

#ifdef HAVE_OVERLAY
   if(string_is_equal("overlay", drivername))
      current_led_driver = &overlay_led_driver;
#endif

#if HAVE_RPILED
   if(string_is_equal("rpi", drivername))
      current_led_driver = &rpi_led_driver;
#endif

   RARCH_LOG("[LED]: LED driver = '%s' %p\n",
         drivername, current_led_driver);

   if(current_led_driver)
      (*current_led_driver->init)();

   return true;
}