#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int* config_devices; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int MAX_INPUT_DEVICES ; 
#define  RETRO_DEVICE_ANALOG 132 
#define  RETRO_DEVICE_JOYPAD 131 
#define  RETRO_DEVICE_KEYBOARD 130 
#define  RETRO_DEVICE_LIGHTGUN 129 
 int RETRO_DEVICE_MASK ; 
#define  RETRO_DEVICE_MOUSE 128 

uint32_t netplay_expected_input_size(netplay_t *netplay, uint32_t devices)
{
   uint32_t ret = 0, device;

   for (device = 0; device < MAX_INPUT_DEVICES; device++)
   {
      if (!(devices & (1<<device)))
         continue;

      switch (netplay->config_devices[device]&RETRO_DEVICE_MASK)
      {
         /* These are all essentially magic numbers, but each device has a
          * fixed size, documented in network/netplay/README */
         case RETRO_DEVICE_JOYPAD:
            ret += 1;
            break;
         case RETRO_DEVICE_MOUSE:
            ret += 2;
            break;
         case RETRO_DEVICE_KEYBOARD:
            ret += 5;
            break;
         case RETRO_DEVICE_LIGHTGUN:
            ret += 2;
            break;
         case RETRO_DEVICE_ANALOG:
            ret += 3;
            break;
         default:
            break; /* Unsupported */
      }
   }

   return ret;
}