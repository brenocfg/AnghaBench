#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int timacnt; int timasd; int scipd; int mcipd; int timbcnt; int timbsd; int timccnt; int timcsd; } ;

/* Variables and functions */
 TYPE_1__ scsp ; 
 int /*<<< orphan*/  scsp_main_interrupt (int) ; 
 int /*<<< orphan*/  scsp_sound_interrupt (int) ; 

void
scsp_update_timer (u32 len)
{
   scsp.timacnt += len << (8 - scsp.timasd);

   if (scsp.timacnt >= 0xFF00)
   {
      if (!(scsp.scipd & 0x40))
         scsp_sound_interrupt(0x40);
      if (!(scsp.mcipd & 0x40))
         scsp_main_interrupt(0x40);
      scsp.timacnt -= 0xFF00;
   }

   scsp.timbcnt += len << (8 - scsp.timbsd);

   if (scsp.timbcnt >= 0xFF00)
   {
      if (!(scsp.scipd & 0x80))
         scsp_sound_interrupt(0x80);
      if (!(scsp.mcipd & 0x80))
         scsp_main_interrupt(0x80);
      scsp.timbcnt -= 0xFF00;
   }

   scsp.timccnt += len << (8 - scsp.timcsd);

   if (scsp.timccnt >= 0xFF00)
   {
      if (!(scsp.scipd & 0x100))
         scsp_sound_interrupt(0x100);
      if (!(scsp.mcipd & 0x100))
         scsp_main_interrupt(0x100);
      scsp.timccnt -= 0xFF00;
   }

   // 1F interrupt can't be accurate here...
   if (len)
   {
      if (!(scsp.scipd & 0x400))
         scsp_sound_interrupt(0x400);
      if (!(scsp.mcipd & 0x400))
         scsp_main_interrupt(0x400);
   }
}