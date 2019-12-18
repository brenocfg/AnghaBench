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
typedef  int uint32 ;
struct TYPE_3__ {int* regs; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 TYPE_2__ cart ; 

__attribute__((used)) static void tekken_regs_w(uint32 address, uint32 data)
{
  switch (address & 0x0e)
  {
    case 0x00:
    {
      /* data output reset ? (game writes $FF before & after protection check) */
      cart.hw.regs[0]= 0x00;
      break;
    }
  
    case 0x02:
    {
      /* read only ? */
      break;
    }
  
    case 0x0c:
    {
      /* data output mode bit 0 ? (game writes $01) */
      break;
    }
  
    case 0x0e:
    {
      /* data output mode bit 1 ? (never written by game) */
      break;
    }
  
    default:
    {
      /* data input (only connected to D0 ?)*/
      if (data & 1)
      {
        /* 4-bit hardware register ($400004 corresponds to bit0, $400006 to bit1, etc) */
        cart.hw.regs[0] |= 1 << (((address - 0x04) >> 1) & 3);
      }
      break;
    }
  }
}