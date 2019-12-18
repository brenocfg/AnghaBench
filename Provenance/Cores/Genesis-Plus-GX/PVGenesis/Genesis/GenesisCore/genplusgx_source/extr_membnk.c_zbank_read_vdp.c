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
 int vdp_68k_ctrl_r (int /*<<< orphan*/ ) ; 
 int vdp_68k_data_r () ; 
 int vdp_hvc_r (int /*<<< orphan*/ ) ; 
 unsigned int zbank_lockup_r (unsigned int) ; 
 unsigned int zbank_unused_r (unsigned int) ; 

unsigned int zbank_read_vdp(unsigned int address)
{
  switch (address & 0xFD)
  {
    case 0x00:    /* DATA */
    {
      return (vdp_68k_data_r() >> 8);
    }
      
    case 0x01:    /* DATA */
    {
      return (vdp_68k_data_r() & 0xFF);
    }
      
    case 0x04:    /* CTRL */
    {
      return (((vdp_68k_ctrl_r(Z80.cycles) >> 8) & 3) | 0xFC);
    }

    case 0x05:    /* CTRL */
    {
      return (vdp_68k_ctrl_r(Z80.cycles) & 0xFF);
    }
      
    case 0x08:    /* HVC */
    case 0x0C:
    {
      return (vdp_hvc_r(Z80.cycles) >> 8);
    }

    case 0x09:    /* HVC */
    case 0x0D:
    {
      return (vdp_hvc_r(Z80.cycles) & 0xFF);
    }

    case 0x18:    /* Unused */
    case 0x19:
    case 0x1C:
    case 0x1D:
    {
      return zbank_unused_r(address);
    }

    default:    /* Invalid address */
    {
      return zbank_lockup_r(address);
    }
  }
}