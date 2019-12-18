#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_3__ {int /*<<< orphan*/  all; } ;
struct TYPE_4__ {int** MD; size_t* CT; int RX; int RA0; int WA0; int jmpaddr; int /*<<< orphan*/  delayed; int /*<<< orphan*/  PC; int /*<<< orphan*/  TOP; int /*<<< orphan*/  LOP; TYPE_1__ P; } ;

/* Variables and functions */
 TYPE_2__* ScuDsp ; 

__attribute__((used)) static void writeloadimdest(u8 num, u32 val)
{
   switch(num) { 
      case 0x0: // MC0
          ScuDsp->MD[0][ScuDsp->CT[0]] = val;
          ScuDsp->CT[0]++;
          ScuDsp->CT[0] &= 0x3f;
          return;
      case 0x1: // MC1
          ScuDsp->MD[1][ScuDsp->CT[1]] = val;
          ScuDsp->CT[1]++;
          ScuDsp->CT[1] &= 0x3f;
          return;
      case 0x2: // MC2
          ScuDsp->MD[2][ScuDsp->CT[2]] = val;
          ScuDsp->CT[2]++;
          ScuDsp->CT[2] &= 0x3f;
          return;
      case 0x3: // MC3
          ScuDsp->MD[3][ScuDsp->CT[3]] = val;
          ScuDsp->CT[3]++;
          ScuDsp->CT[3] &= 0x3f;
          return;
      case 0x4: // RX
          ScuDsp->RX = val;
          return;
      case 0x5: // PL
          ScuDsp->P.all = (s64)val;
          return;
      case 0x6: // RA0
          val = (val & 0x1FFFFFF);
          ScuDsp->RA0 = val;
          return;
      case 0x7: // WA0
          val = (val & 0x1FFFFFF);
          ScuDsp->WA0 = val;
          return;
      case 0xA: // LOP
          ScuDsp->LOP = (u16)val;
          return;
      case 0xC: // PC->TOP, PC
          ScuDsp->TOP = ScuDsp->PC+1;
          ScuDsp->jmpaddr = val;
          ScuDsp->delayed = 0;
          return;
      default: break;
   }
}