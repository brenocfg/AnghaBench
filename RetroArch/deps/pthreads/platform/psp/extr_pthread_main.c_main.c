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
struct TYPE_3__ {int Buttons; } ;
typedef  TYPE_1__ SceCtrlData ;

/* Variables and functions */
 int PSP_CTRL_UP ; 
 int /*<<< orphan*/  SetupCallbacks () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pspDebugScreenInit () ; 
 int /*<<< orphan*/  pte_test_main () ; 
 int /*<<< orphan*/  sceCtrlReadBufferPositive (TYPE_1__*,int) ; 

int main(void)
{
   SceCtrlData pad;

   pspDebugScreenInit();
   SetupCallbacks();

   pte_test_main();

   while (1)
   {
      sceCtrlReadBufferPositive(&pad, 1);
      if (pad.Buttons & PSP_CTRL_UP)
      {
         printf("Exiting...\n");
         return 0;
      }

   }
   return 0;
}