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
typedef  enum camera_driver_enum { ____Placeholder_camera_driver_enum } camera_driver_enum ;

/* Variables and functions */
#define  CAMERA_ANDROID 132 
#define  CAMERA_AVFOUNDATION 131 
 int CAMERA_DEFAULT_DRIVER ; 
#define  CAMERA_NULL 130 
#define  CAMERA_RWEBCAM 129 
#define  CAMERA_V4L2 128 

const char *config_get_default_camera(void)
{
   enum camera_driver_enum default_driver = CAMERA_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case CAMERA_V4L2:
         return "video4linux2";
      case CAMERA_RWEBCAM:
         return "rwebcam";
      case CAMERA_ANDROID:
         return "android";
      case CAMERA_AVFOUNDATION:
         return "avfoundation";
      case CAMERA_NULL:
         break;
   }

   return "null";
}