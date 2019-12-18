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
struct TYPE_2__ {int cartid; int /*<<< orphan*/  bupram; } ;

/* Variables and functions */
 int /*<<< orphan*/  BupRam ; 
 TYPE_1__* CartridgeArea ; 
 int /*<<< orphan*/  FormatBackupRam (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOG (char*) ; 

void BupFormat(u32 device)
{
   switch (device)
   {
      case 0:
         FormatBackupRam(BupRam, 0x10000);
         break;
      case 1:
         if ((CartridgeArea->cartid & 0xF0) == 0x20)
         {
            switch (CartridgeArea->cartid & 0xF)
            {
               case 1:
                  FormatBackupRam(CartridgeArea->bupram, 0x100000);
                  break;
               case 2:
                  FormatBackupRam(CartridgeArea->bupram, 0x200000);
                  break;
               case 3:
                  FormatBackupRam(CartridgeArea->bupram, 0x400000);
                  break;
               case 4:
                  FormatBackupRam(CartridgeArea->bupram, 0x800000);
                  break;
               default: break;
            }
         }
         break;
      case 2:
         LOG("Formatting FDD not supported\n");
      default: break;
   }
}