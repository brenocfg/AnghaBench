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
 int RETRO_DEVICE_MOUSE ; 

__attribute__((used)) static uint64_t ps3_input_get_capabilities(void *data)
{
   (void)data;
   return
#ifdef HAVE_MOUSE
      (1 << RETRO_DEVICE_MOUSE)  |
#endif
      (1 << RETRO_DEVICE_JOYPAD) |
      (1 << RETRO_DEVICE_ANALOG);
}