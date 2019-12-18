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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {size_t* CT; int /*<<< orphan*/ ** MD; } ;

/* Variables and functions */
 TYPE_1__* ScuDsp ; 

__attribute__((used)) static u32 readdmasrc(u8 num, u8 add)
{
   u32 val;

   switch(num) {
      case 0x0: // M0
         val = ScuDsp->MD[0][ScuDsp->CT[0]];
         ScuDsp->CT[0]+=add;
         return val;
      case 0x1: // M1
         val = ScuDsp->MD[1][ScuDsp->CT[1]];
         ScuDsp->CT[1]+=add;
         return val;
      case 0x2: // M2
         val = ScuDsp->MD[2][ScuDsp->CT[2]];
         ScuDsp->CT[2]+=add;
         return val;
      case 0x3: // M3
         val = ScuDsp->MD[3][ScuDsp->CT[3]];
         ScuDsp->CT[3]+=add;
         return val;
      default: break;
   }

   return 0;
}