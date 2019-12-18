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
struct TYPE_3__ {int* mask; int* addr; int* regs; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 TYPE_2__ cart ; 
 int m68k_read_bus_8 (int) ; 

__attribute__((used)) static uint32 custom_regs_r(uint32 address)
{
  int i;
  for (i=0; i<4; i++)
  {
    if ((address & cart.hw.mask[i]) == cart.hw.addr[i])
    {
      return cart.hw.regs[i] >> 1;
    }
  }

  return m68k_read_bus_8(address);
}