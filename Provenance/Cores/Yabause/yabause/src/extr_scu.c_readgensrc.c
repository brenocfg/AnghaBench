#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
struct TYPE_5__ {int all; TYPE_1__ part; } ;
struct TYPE_6__ {size_t* CT; TYPE_2__ ALU; int /*<<< orphan*/ ** MD; } ;

/* Variables and functions */
 TYPE_3__* ScuDsp ; 
 int* incFlg ; 

__attribute__((used)) static u32 readgensrc(u8 num)
{
   u32 val;
   switch(num) {
      case 0x0: // M0
         return ScuDsp->MD[0][ScuDsp->CT[0]];
      case 0x1: // M1
         return ScuDsp->MD[1][ScuDsp->CT[1]];
      case 0x2: // M2
         return ScuDsp->MD[2][ScuDsp->CT[2]];
      case 0x3: // M3
         return ScuDsp->MD[3][ScuDsp->CT[3]];
      case 0x4: // MC0
         val = ScuDsp->MD[0][ScuDsp->CT[0]];
         incFlg[0] = 1;
         return val;
      case 0x5: // MC1
         val = ScuDsp->MD[1][ScuDsp->CT[1]];
         incFlg[1] = 1;
         return val;
      case 0x6: // MC2
         val = ScuDsp->MD[2][ScuDsp->CT[2]];
         incFlg[2] = 1;
         return val;
      case 0x7: // MC3
         val = ScuDsp->MD[3][ScuDsp->CT[3]];
         incFlg[3] = 1;
         return val;
      case 0x9: // ALL
         return (u32)ScuDsp->ALU.part.L;
      case 0xA: // ALH
         return (u32)((ScuDsp->ALU.all & (u64)(0x0000ffffffff0000))  >> 16);
      default: break;
   }

   return 0;
}