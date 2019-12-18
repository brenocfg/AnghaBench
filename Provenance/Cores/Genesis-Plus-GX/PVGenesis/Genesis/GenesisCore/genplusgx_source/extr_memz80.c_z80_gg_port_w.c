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
struct TYPE_2__ {scalar_t__ cycles; } ;

/* Variables and functions */
 scalar_t__ SMS_CYCLE_OFFSET ; 
 int /*<<< orphan*/  SN76489_Write (scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  SYSTEM_GG ; 
 TYPE_1__ Z80 ; 
 int /*<<< orphan*/  io_gg_write (unsigned int,unsigned char) ; 
 int /*<<< orphan*/  io_z80_write (unsigned int,unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  system_hw ; 
 int /*<<< orphan*/  vdp_sms_ctrl_w (unsigned char) ; 
 int /*<<< orphan*/  vdp_z80_data_w (unsigned char) ; 
 int /*<<< orphan*/  z80_unused_port_w (unsigned int,unsigned char) ; 

void z80_gg_port_w(unsigned int port, unsigned char data)
{
  switch(port & 0xC1)
  {
    case 0x00:
    case 0x01:
    {
      port &= 0xFF;

      if (port < 0x07)
      {
        if (system_hw == SYSTEM_GG)
        {
          io_gg_write(port, data);
          return;
        }

        z80_unused_port_w(port & 0xFF, data);
        return;
      }

      io_z80_write(port & 1, data, Z80.cycles + SMS_CYCLE_OFFSET);
      return;
    }

    case 0x40:
    case 0x41:
    {
      SN76489_Write(Z80.cycles, data);
      return;
    }

    case 0x80:
    {
      vdp_z80_data_w(data);
      return;
    }

    case 0x81:
    {
      vdp_sms_ctrl_w(data);
      return;
    }

    default:
    {
      z80_unused_port_w(port & 0xFF, data);
      return;
    }
  }
}