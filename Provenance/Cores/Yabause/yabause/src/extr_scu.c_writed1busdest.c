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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int all; } ;
struct TYPE_4__ {size_t* CT; int TOP; int /*<<< orphan*/  LOP; void* WA0; void* RA0; TYPE_1__ P; void* RX; void*** MD; } ;

/* Variables and functions */
 TYPE_2__* ScuDsp ; 

__attribute__((used)) static void writed1busdest(u8 num, u32 val)
{
   switch(num) { 
      case 0x0:
          ScuDsp->MD[0][ScuDsp->CT[0]] = val;
          ScuDsp->CT[0]++;
          ScuDsp->CT[0] &= 0x3f;
          return;
      case 0x1:
          ScuDsp->MD[1][ScuDsp->CT[1]] = val;
          ScuDsp->CT[1]++;
          ScuDsp->CT[1] &= 0x3f;
          return;
      case 0x2:
          ScuDsp->MD[2][ScuDsp->CT[2]] = val;
          ScuDsp->CT[2]++;
          ScuDsp->CT[2] &= 0x3f;
          return;
      case 0x3:
          ScuDsp->MD[3][ScuDsp->CT[3]] = val;
          ScuDsp->CT[3]++;
          ScuDsp->CT[3] &= 0x3f;
          return;
      case 0x4:
          ScuDsp->RX = val;
          return;
      case 0x5:
          ScuDsp->P.all = (signed)val;
          return;
      case 0x6:
          ScuDsp->RA0 = val;
          return;
      case 0x7:
          ScuDsp->WA0 = val;
          return;
      case 0xA:
          ScuDsp->LOP = (u16)val;
          return;
      case 0xB:
          ScuDsp->TOP = (u8)val;
          return;
      case 0xC:
          ScuDsp->CT[0] = (u8)val;
          return;
      case 0xD:
          ScuDsp->CT[1] = (u8)val;
          return;
      case 0xE:
          ScuDsp->CT[2] = (u8)val;
          return;
      case 0xF:
          ScuDsp->CT[3] = (u8)val;
          return;
      default: break;
   }
}