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
typedef  int uint8 ;
typedef  int uint32 ;
struct TYPE_3__ {int* regs; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 TYPE_2__ cart ; 
 int /*<<< orphan*/  default_regs_w (int,int) ; 
 int /*<<< orphan*/  mapper_32k_w (int) ; 

__attribute__((used)) static void custom_regs_w(uint32 address, uint32 data)
{
  uint8 temp;
  
  /* ROM bankswitch */
  if ((address >> 16) > 0x6f)
  {
    mapper_32k_w(data);
    return;
  }

  /* write register */
  default_regs_w(address, data);

  /* bitswapping */
  temp = cart.hw.regs[0];
  switch (cart.hw.regs[1] & 3)
  {
    case 0:
      cart.hw.regs[2] = (temp << 1);
      break;

    case 1:
      cart.hw.regs[2] = (temp >> 1);
      return;

    case 2:
      cart.hw.regs[2] = ((temp >> 4) | ((temp & 0x0F) << 4));
      return;

    default:
      cart.hw.regs[2] = (((temp >> 7) & 0x01) | ((temp >> 5) & 0x02) |
                         ((temp >> 3) & 0x04) | ((temp >> 1) & 0x08) |
                         ((temp << 1) & 0x10) | ((temp << 3) & 0x20) |
                         ((temp << 5) & 0x40) | ((temp << 7) & 0x80));
      return;
  }
}