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
typedef  int uint16_t ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 size_t DOSKEY_DOWN ; 
 size_t DOSKEY_LEFT ; 
 size_t DOSKEY_RETURN ; 
 size_t DOSKEY_RIGHT ; 
 size_t DOSKEY_RSHIFT ; 
 size_t DOSKEY_UP ; 
 size_t DOSKEY_a ; 
 size_t DOSKEY_s ; 
 size_t DOSKEY_x ; 
 size_t DOSKEY_z ; 
#define  RETRO_DEVICE_ID_JOYPAD_A 137 
#define  RETRO_DEVICE_ID_JOYPAD_B 136 
#define  RETRO_DEVICE_ID_JOYPAD_DOWN 135 
#define  RETRO_DEVICE_ID_JOYPAD_LEFT 134 
#define  RETRO_DEVICE_ID_JOYPAD_RIGHT 133 
#define  RETRO_DEVICE_ID_JOYPAD_SELECT 132 
#define  RETRO_DEVICE_ID_JOYPAD_START 131 
#define  RETRO_DEVICE_ID_JOYPAD_UP 130 
#define  RETRO_DEVICE_ID_JOYPAD_X 129 
#define  RETRO_DEVICE_ID_JOYPAD_Y 128 
 int* dos_keyboard_state_get (unsigned int) ; 

__attribute__((used)) static bool dos_joypad_button(unsigned port_num, uint16_t key)
{
   uint16_t *buf = dos_keyboard_state_get(port_num);

   if (port_num >= DEFAULT_MAX_PADS)
      return false;

   switch (key)
   {
      case RETRO_DEVICE_ID_JOYPAD_A:
         return buf[DOSKEY_x];
      case RETRO_DEVICE_ID_JOYPAD_B:
         return buf[DOSKEY_z];
      case RETRO_DEVICE_ID_JOYPAD_X:
         return buf[DOSKEY_s];
      case RETRO_DEVICE_ID_JOYPAD_Y:
         return buf[DOSKEY_a];
      case RETRO_DEVICE_ID_JOYPAD_SELECT:
         return buf[DOSKEY_RSHIFT];
      case RETRO_DEVICE_ID_JOYPAD_START:
         return buf[DOSKEY_RETURN];
      case RETRO_DEVICE_ID_JOYPAD_UP:
         return buf[DOSKEY_UP];
      case RETRO_DEVICE_ID_JOYPAD_DOWN:
         return buf[DOSKEY_DOWN];
      case RETRO_DEVICE_ID_JOYPAD_LEFT:
         return buf[DOSKEY_LEFT];
      case RETRO_DEVICE_ID_JOYPAD_RIGHT:
         return buf[DOSKEY_RIGHT];
   }

   return false;
}