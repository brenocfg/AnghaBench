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
typedef  int u32 ;

/* Variables and functions */
 int KEY_SELECT ; 
 int KEY_START ; 
 scalar_t__ aptMainLoop () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int hidKeysDown () ; 
 int /*<<< orphan*/  hidScanInput () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int select_pressed ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  svcSleepThread (int) ; 

void wait_for_input(void)
{
   printf("\n\nPress Start.\n\n");
   fflush(stdout);

   while (aptMainLoop())
   {
      u32 kDown;

      hidScanInput();

      kDown = hidKeysDown();

      if (kDown & KEY_START)
         break;

      if (kDown & KEY_SELECT)
         exit(0);

#if 0
      select_pressed = true;
#endif

      svcSleepThread(1000000);
   }
}