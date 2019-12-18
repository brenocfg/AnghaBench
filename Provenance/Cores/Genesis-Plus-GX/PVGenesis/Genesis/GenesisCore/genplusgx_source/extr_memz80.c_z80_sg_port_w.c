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
 int /*<<< orphan*/  SN76489_Write (int /*<<< orphan*/ ,unsigned char) ; 
 TYPE_1__ Z80 ; 
 int /*<<< orphan*/  vdp_tms_ctrl_w (unsigned char) ; 
 int /*<<< orphan*/  vdp_z80_data_w (unsigned char) ; 
 int /*<<< orphan*/  z80_unused_port_w (unsigned int,unsigned char) ; 

void z80_sg_port_w(unsigned int port, unsigned char data)
{
  switch(port & 0xC1)
  {
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
      vdp_tms_ctrl_w(data);
      return;
    }

    default:
    {
      z80_unused_port_w(port & 0xFF, data);
      return;
    }
  }
}