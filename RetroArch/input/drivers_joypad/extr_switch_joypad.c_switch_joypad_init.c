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
struct TYPE_3__ {float amp_low; float freq_low; float amp_high; float freq_high; } ;
typedef  int /*<<< orphan*/  HidVibrationValue ;

/* Variables and functions */
 unsigned int CONTROLLER_HANDHELD ; 
 unsigned int DEFAULT_MAX_PADS ; 
 int TYPE_HANDHELD ; 
 int TYPE_JOYCON_PAIR ; 
 int /*<<< orphan*/  hidInitializeVibrationDevices (int /*<<< orphan*/ ,int,unsigned int,int) ; 
 int /*<<< orphan*/  hidScanInput () ; 
 int /*<<< orphan*/  hid_init () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  switch_joypad_autodetect_add (int) ; 
 int /*<<< orphan*/  vibration_handleheld ; 
 int /*<<< orphan*/ * vibration_handles ; 
 TYPE_1__ vibration_stop ; 
 int /*<<< orphan*/ ** vibration_values ; 

__attribute__((used)) static bool switch_joypad_init(void *data)
{
#ifdef HAVE_LIBNX
   unsigned i;
   hidScanInput();

   /* Switch like stop behavior with muted band channels 
    * and frequencies set to default. */
   vibration_stop.amp_low   = 0.0f;
   vibration_stop.freq_low  = 160.0f;
   vibration_stop.amp_high  = 0.0f;
   vibration_stop.freq_high = 320.0f;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      switch_joypad_autodetect_add(i);
      hidInitializeVibrationDevices(
            vibration_handles[i], 2, i,
            TYPE_HANDHELD | TYPE_JOYCON_PAIR);
      memcpy(&vibration_values[i][0],
            &vibration_stop, sizeof(HidVibrationValue));
      memcpy(&vibration_values[i][1],
            &vibration_stop, sizeof(HidVibrationValue));
   }
   hidInitializeVibrationDevices(vibration_handleheld,
         2, CONTROLLER_HANDHELD, TYPE_HANDHELD | TYPE_JOYCON_PAIR);
#else
   hid_init();
   switch_joypad_autodetect_add(0);
   switch_joypad_autodetect_add(1);
#endif

   return true;
}