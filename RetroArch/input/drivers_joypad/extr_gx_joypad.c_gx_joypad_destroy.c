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

/* Variables and functions */
 int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  WPADDisconnect (int) ; 
 int /*<<< orphan*/  WPAD_Flush (int) ; 

__attribute__((used)) static void gx_joypad_destroy(void)
{
#ifdef HW_RVL
#if 0
   int i;
   for (i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      /* Commenting this out fixes the Wii
       * remote not reconnecting after
       * core load, exit, etc. */
      WPAD_Flush(i);
      WPADDisconnect(i);
   }
#endif
#endif
}