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
struct TYPE_4__ {scalar_t__ cycles; } ;
struct TYPE_3__ {int ym2413; } ;

/* Variables and functions */
 scalar_t__ PBC_CYCLE_OFFSET ; 
 int /*<<< orphan*/  SN76489_Write (scalar_t__,unsigned char) ; 
 TYPE_2__ Z80 ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  fm_write (scalar_t__,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  io_z80_write (int,unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  vdp_z80_ctrl_w (unsigned char) ; 
 int /*<<< orphan*/  vdp_z80_data_w (unsigned char) ; 
 int /*<<< orphan*/  z80_unused_port_w (unsigned int,unsigned char) ; 

void z80_md_port_w(unsigned int port, unsigned char data)
{
  switch (port & 0xC1)
  {
    case 0x01:
    {
      io_z80_write(1, data, Z80.cycles + PBC_CYCLE_OFFSET);
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
      vdp_z80_ctrl_w(data);
      return;
    }

    default:
    {
      port &= 0xFF;

      if ((port >= 0xF0) && (config.ym2413 & 1))
      {
        fm_write(Z80.cycles, port&3, data);
        return;
      }

      z80_unused_port_w(port, data);
      return;
    }
  }
}