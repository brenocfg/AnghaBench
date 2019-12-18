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
typedef  int /*<<< orphan*/  HidVibrationValue ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/  hidSendVibrationValues (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hid_finalize () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int previous_handheld ; 
 scalar_t__* previous_split_joycon_setting ; 
 int /*<<< orphan*/  vibration_handleheld ; 
 int /*<<< orphan*/ * vibration_handles ; 
 int /*<<< orphan*/  vibration_stop ; 
 int /*<<< orphan*/ ** vibration_values ; 

__attribute__((used)) static void switch_joypad_destroy(void)
{
#ifdef HAVE_LIBNX
   unsigned i;

   previous_handheld = -1;

   for (i = 0; i < MAX_USERS; i++)
      previous_split_joycon_setting[i] = 0;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      memcpy(&vibration_values[i][0],
            &vibration_stop, sizeof(HidVibrationValue));
      memcpy(&vibration_values[i][1],
            &vibration_stop, sizeof(HidVibrationValue));
      hidSendVibrationValues(vibration_handles[i], vibration_values[i], 2);
   }
   hidSendVibrationValues(vibration_handleheld, vibration_values[0], 2);
#else
   hid_finalize();
#endif
}