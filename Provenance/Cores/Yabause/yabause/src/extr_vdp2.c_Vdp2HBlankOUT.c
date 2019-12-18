#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  Vdp2 ;
struct TYPE_9__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int all; } ;
struct TYPE_8__ {int TVSTAT; TYPE_1__ VCSTA; } ;
struct TYPE_7__ {int LineCount; } ;

/* Variables and functions */
 scalar_t__ Vdp2Lines ; 
 int /*<<< orphan*/  Vdp2RamReadLong (int) ; 
 TYPE_3__* Vdp2Regs ; 
 TYPE_4__* cell_scroll_data ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_3__*,int) ; 
 TYPE_2__ yabsys ; 

void Vdp2HBlankOUT(void) {
   int i;
   Vdp2Regs->TVSTAT &= ~0x0004;

   if (yabsys.LineCount < 270)
   {
      u32 cell_scroll_table_start_addr = (Vdp2Regs->VCSTA.all & 0x7FFFE) << 1;
      memcpy(Vdp2Lines + yabsys.LineCount, Vdp2Regs, sizeof(Vdp2));

      for (i = 0; i < 88; i++)
      {
         cell_scroll_data[yabsys.LineCount].data[i] = Vdp2RamReadLong(cell_scroll_table_start_addr + i * 4);
      }
   }
}