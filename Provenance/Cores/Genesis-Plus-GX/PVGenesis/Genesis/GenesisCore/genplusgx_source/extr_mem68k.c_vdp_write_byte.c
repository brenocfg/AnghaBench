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
struct TYPE_2__ {int /*<<< orphan*/  cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  SN76489_Write (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__ m68k ; 
 int /*<<< orphan*/  m68k_lockup_w_8 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  m68k_unused_8_w (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vdp_68k_ctrl_w (unsigned int) ; 
 int /*<<< orphan*/  vdp_68k_data_w (unsigned int) ; 
 int /*<<< orphan*/  vdp_test_w (unsigned int) ; 

void vdp_write_byte(unsigned int address, unsigned int data)
{
  switch (address & 0xFC)
  {
    case 0x00:  /* Data port */
    {
      vdp_68k_data_w(data << 8 | data);
      return;
    }

    case 0x04:  /* Control port */
    {
      vdp_68k_ctrl_w(data << 8 | data);
      return;
    }

    case 0x10:  /* PSG */
    case 0x14:
    {
      if (address & 1)
      {
        SN76489_Write(m68k.cycles, data);
        return;
      }
      m68k_unused_8_w(address, data);
      return;
    }

    case 0x18: /* Unused */
    {
      m68k_unused_8_w(address, data);
      return;
    }

    case 0x1C:  /* TEST register */
    {
      vdp_test_w(data << 8 | data);
      return;
    }

    default:  /* Invalid address */
    {
      m68k_lockup_w_8(address, data);
      return;
    }
  }
}