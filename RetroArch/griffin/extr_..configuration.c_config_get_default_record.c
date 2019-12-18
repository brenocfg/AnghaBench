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
typedef  enum record_driver_enum { ____Placeholder_record_driver_enum } record_driver_enum ;

/* Variables and functions */
 int RECORD_DEFAULT_DRIVER ; 
#define  RECORD_FFMPEG 129 
#define  RECORD_NULL 128 

const char *config_get_default_record(void)
{
   enum record_driver_enum default_driver = RECORD_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case RECORD_FFMPEG:
         return "ffmpeg";
      case RECORD_NULL:
         break;
   }

   return "null";
}