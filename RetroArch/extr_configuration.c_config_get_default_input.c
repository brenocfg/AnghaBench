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
typedef  enum input_driver_enum { ____Placeholder_input_driver_enum } input_driver_enum ;

/* Variables and functions */
#define  INPUT_ANDROID 152 
#define  INPUT_COCOA 151 
#define  INPUT_CTR 150 
 int INPUT_DEFAULT_DRIVER ; 
#define  INPUT_DINPUT 149 
#define  INPUT_DOS 148 
#define  INPUT_LINUXRAW 147 
#define  INPUT_NULL 146 
#define  INPUT_PS2 145 
#define  INPUT_PS3 144 
#define  INPUT_PS4 143 
#define  INPUT_PSP 142 
#define  INPUT_QNX 141 
#define  INPUT_RWEBINPUT 140 
#define  INPUT_SDL 139 
#define  INPUT_SDL2 138 
#define  INPUT_SWITCH 137 
#define  INPUT_UDEV 136 
#define  INPUT_UWP 135 
#define  INPUT_WAYLAND 134 
#define  INPUT_WII 133 
#define  INPUT_WIIU 132 
#define  INPUT_WINRAW 131 
#define  INPUT_X 130 
#define  INPUT_XENON360 129 
#define  INPUT_XINPUT 128 

const char *config_get_default_input(void)
{
   enum input_driver_enum default_driver = INPUT_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case INPUT_ANDROID:
         return "android";
      case INPUT_PS4:
         return "ps4";
      case INPUT_PS3:
         return "ps3";
      case INPUT_PSP:
#ifdef VITA
         return "vita";
#else
         return "psp";
#endif
      case INPUT_PS2:
         return "ps2";
      case INPUT_CTR:
         return "ctr";
      case INPUT_SWITCH:
         return "switch";
      case INPUT_SDL:
         return "sdl";
      case INPUT_SDL2:
         return "sdl2";
      case INPUT_DINPUT:
         return "dinput";
      case INPUT_WINRAW:
         return "raw";
      case INPUT_X:
         return "x";
      case INPUT_WAYLAND:
         return "wayland";
      case INPUT_XENON360:
         return "xenon360";
      case INPUT_XINPUT:
         return "xinput";
      case INPUT_UWP:
         return "uwp";
      case INPUT_WII:
         return "gx";
      case INPUT_WIIU:
         return "wiiu";
      case INPUT_LINUXRAW:
         return "linuxraw";
      case INPUT_UDEV:
         return "udev";
      case INPUT_COCOA:
         return "cocoa";
      case INPUT_QNX:
          return "qnx_input";
      case INPUT_RWEBINPUT:
          return "rwebinput";
      case INPUT_DOS:
         return "dos";
      case INPUT_NULL:
          break;
   }

   return "null";
}