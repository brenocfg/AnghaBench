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
typedef  int uint64_t ;

/* Variables and functions */
 int RETRO_DEVICE_ANALOG ; 
 int RETRO_DEVICE_JOYPAD ; 
 int RETRO_DEVICE_KEYBOARD ; 
 int RETRO_DEVICE_MOUSE ; 
 int RETRO_DEVICE_POINTER ; 

__attribute__((used)) static uint64_t rwebinput_get_capabilities(void *data)
{
   uint64_t caps = 0;

   caps |= (1 << RETRO_DEVICE_JOYPAD);
   caps |= (1 << RETRO_DEVICE_ANALOG);
   caps |= (1 << RETRO_DEVICE_KEYBOARD);
   caps |= (1 << RETRO_DEVICE_MOUSE);
   caps |= (1 << RETRO_DEVICE_POINTER);

   return caps;
}