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
typedef  int u16 ;
struct TYPE_2__ {int data; int address; } ;

/* Variables and functions */
 int* cheatIndexes ; 
 TYPE_1__* cheatlist ; 
 int maxRAMcheats ; 
 int* work_ram ; 

void RAMCheatUpdate(void)
{
  int index, cnt = maxRAMcheats;
  
  while (cnt)
  {
    /* get cheat index */
    index = cheatIndexes[--cnt];

    /* apply RAM patch */
    if (cheatlist[index].data & 0xFF00)
    {
      /* word patch */
      *(u16 *)(work_ram + (cheatlist[index].address & 0xFFFE)) = cheatlist[index].data;
    }
    else
    {
      /* byte patch */
      work_ram[cheatlist[index].address & 0xFFFF] = cheatlist[index].data;
    }
  }
}