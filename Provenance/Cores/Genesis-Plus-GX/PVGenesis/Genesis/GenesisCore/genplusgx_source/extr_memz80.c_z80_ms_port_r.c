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
struct TYPE_4__ {int /*<<< orphan*/  cycles; } ;
struct TYPE_3__ {int ym2413; } ;

/* Variables and functions */
 unsigned char YM2413Read (unsigned int) ; 
 TYPE_2__ Z80 ; 
 TYPE_1__ config ; 
 int* io_reg ; 
 unsigned char io_z80_read (unsigned int) ; 
 int vdp_hvc_r (int /*<<< orphan*/ ) ; 
 unsigned char vdp_z80_ctrl_r (int /*<<< orphan*/ ) ; 
 unsigned char vdp_z80_data_r () ; 
 unsigned char z80_unused_port_r (unsigned int) ; 

unsigned char z80_ms_port_r(unsigned int port)
{
  switch (port & 0xC1)
  {
    case 0x00:
    case 0x01:
    {
      return z80_unused_port_r(port & 0xFF);
    }

    case 0x40:
    {
      return ((vdp_hvc_r(Z80.cycles) >> 8) & 0xFF);
    }

    case 0x41:
    {
      return (vdp_hvc_r(Z80.cycles) & 0xFF);
    }

    case 0x80:
    {
      return vdp_z80_data_r();
    }

    case 0x81:
    {
      return vdp_z80_ctrl_r(Z80.cycles);
    }

    default:
    {
      /* read FM chip if enabled */
      if (!(port & 4) && (config.ym2413 & 1))
      {
        /* check if I/O ports are disabled */
        if (io_reg[0x0E] & 0x04)
        {
          return YM2413Read(port & 3);
        }
        else
        {
          return YM2413Read(port & 3) & io_z80_read(port & 1);
        }
      }

      /* check if I/O ports are enabled */
      if (!(io_reg[0x0E] & 0x04))
      {
        return io_z80_read(port & 1);
      }

      return z80_unused_port_r(port & 0xFF);
    }
  }
}