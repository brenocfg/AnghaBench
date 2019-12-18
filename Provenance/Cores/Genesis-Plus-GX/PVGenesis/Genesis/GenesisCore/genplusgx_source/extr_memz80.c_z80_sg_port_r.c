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
 TYPE_1__ Z80 ; 
 unsigned char io_z80_read (unsigned int) ; 
 unsigned char vdp_z80_ctrl_r (int /*<<< orphan*/ ) ; 
 unsigned char vdp_z80_data_r () ; 
 unsigned char z80_unused_port_r (unsigned int) ; 

unsigned char z80_sg_port_r(unsigned int port)
{
  switch (port & 0xC1)
  {
    case 0x80:
    {
      return vdp_z80_data_r();
    }

    case 0x81:
    {
      return vdp_z80_ctrl_r(Z80.cycles);
    }

    case 0xC0:
    case 0xC1:
    {
      return io_z80_read(port & 1);
    }

    default:
    {
      return z80_unused_port_r(port);
    }
  }
}