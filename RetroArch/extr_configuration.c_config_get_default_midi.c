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
typedef  enum midi_driver_enum { ____Placeholder_midi_driver_enum } midi_driver_enum ;

/* Variables and functions */
#define  MIDI_ALSA 130 
 int MIDI_DEFAULT_DRIVER ; 
#define  MIDI_NULL 129 
#define  MIDI_WINMM 128 

const char *config_get_default_midi(void)
{
   enum midi_driver_enum default_driver = MIDI_DEFAULT_DRIVER;

   switch (default_driver)
   {
      case MIDI_WINMM:
         return "winmm";
      case MIDI_ALSA:
         return "alsa";
      case MIDI_NULL:
         break;
   }

   return "null";
}