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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/  FCEUD_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCEUI_Emulate (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int FCEUI_EmulationPaused () ; 
 scalar_t__ NoWaiting ; 
 int /*<<< orphan*/  SilenceSound (int) ; 
 int frameskip ; 

void DoFun(void)
{
         uint8 *gfx;  
         int32 *sound;
         int32 ssize;
         static int fskipc=0;
         static int opause=0;
         
         #ifdef FRAMESKIP
         fskipc=(fskipc+1)%(frameskip+1);
         #endif
         
         if(NoWaiting) {gfx=0;}
         FCEUI_Emulate(&gfx, &sound, &ssize, fskipc);
         FCEUD_Update(gfx, sound, ssize);

         if(opause!=FCEUI_EmulationPaused())
         {
          opause=FCEUI_EmulationPaused();
		  SilenceSound(opause);
         }
}