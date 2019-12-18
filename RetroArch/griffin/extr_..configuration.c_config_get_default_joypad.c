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
typedef  enum joypad_driver_enum { ____Placeholder_joypad_driver_enum } joypad_driver_enum ;

/* Variables and functions */
#define  JOYPAD_ANDROID 148 
#define  JOYPAD_CTR 147 
 int JOYPAD_DEFAULT_DRIVER ; 
#define  JOYPAD_DINPUT 146 
#define  JOYPAD_DOS 145 
#define  JOYPAD_GX 144 
#define  JOYPAD_HID 143 
#define  JOYPAD_LINUXRAW 142 
#define  JOYPAD_MFI 141 
#define  JOYPAD_NULL 140 
#define  JOYPAD_PS2 139 
#define  JOYPAD_PS3 138 
#define  JOYPAD_PS4 137 
#define  JOYPAD_PSP 136 
#define  JOYPAD_QNX 135 
#define  JOYPAD_RWEBPAD 134 
#define  JOYPAD_SDL 133 
#define  JOYPAD_SWITCH 132 
#define  JOYPAD_UDEV 131 
#define  JOYPAD_WIIU 130 
#define  JOYPAD_XDK 129 
#define  JOYPAD_XINPUT 128 

const char *config_get_default_joypad(void)
{
   enum joypad_driver_enum default_driver = JOYPAD_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case JOYPAD_PS4:
         return "ps4";
      case JOYPAD_PS3:
         return "ps3";
      case JOYPAD_XINPUT:
         return "xinput";
      case JOYPAD_GX:
         return "gx";
      case JOYPAD_WIIU:
         return "wiiu";
      case JOYPAD_XDK:
         return "xdk";
      case JOYPAD_PSP:
#ifdef VITA
         return "vita";
#else
         return "psp";
#endif
      case JOYPAD_PS2:
         return "ps2";
      case JOYPAD_CTR:
         return "ctr";
      case JOYPAD_SWITCH:
         return "switch";
      case JOYPAD_DINPUT:
         return "dinput";
      case JOYPAD_UDEV:
         return "udev";
      case JOYPAD_LINUXRAW:
         return "linuxraw";
      case JOYPAD_ANDROID:
         return "android";
      case JOYPAD_SDL:
#ifdef HAVE_SDL2
         return "sdl2";
#else
         return "sdl";
#endif
      case JOYPAD_HID:
         return "hid";
      case JOYPAD_QNX:
         return "qnx";
      case JOYPAD_RWEBPAD:
         return "rwebpad";
      case JOYPAD_DOS:
         return "dos";
      case JOYPAD_MFI:
         return "mfi";
      case JOYPAD_NULL:
         break;
   }

   return "null";
}