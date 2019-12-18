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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 129 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 128 
 int /*<<< orphan*/  x11_mouse_hwd ; 
 int /*<<< orphan*/  x11_mouse_hwu ; 
 int /*<<< orphan*/  x11_mouse_wd ; 
 int /*<<< orphan*/  x11_mouse_wu ; 

int16_t x_mouse_state_wheel(unsigned id)
{
   int16_t ret = 0;

   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         ret = x11_mouse_wu;
         x11_mouse_wu = 0;
         return ret;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         ret = x11_mouse_wd;
         x11_mouse_wd = 0;
         return ret;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
         ret = x11_mouse_hwu;
         x11_mouse_hwu = 0;
         return ret;
      case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
         ret = x11_mouse_hwd;
         x11_mouse_hwd = 0;
         return ret;
   }

   return 0;
}