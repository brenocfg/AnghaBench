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

/* Variables and functions */
 scalar_t__ vc_gencmd (char*,int,char*) ; 
 int /*<<< orphan*/  vc_gencmd_number_property (char*,char*,int*) ; 

__attribute__((used)) static void raspicamcontrol_get_camera(int *supported, int *detected)
{
   char response[80] = "";
   if (vc_gencmd(response, sizeof response, "get_camera") == 0)
   {
      if (supported)
         vc_gencmd_number_property(response, "supported", supported);
      if (detected)
         vc_gencmd_number_property(response, "detected", detected);
   }
}