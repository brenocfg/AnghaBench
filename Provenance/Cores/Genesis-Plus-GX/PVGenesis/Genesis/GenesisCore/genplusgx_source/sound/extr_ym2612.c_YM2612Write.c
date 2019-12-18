#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int address; } ;
struct TYPE_5__ {TYPE_1__ ST; } ;
struct TYPE_6__ {int dacout; unsigned int dacen; TYPE_2__ OPN; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPNWriteMode (int,unsigned int) ; 
 int /*<<< orphan*/  OPNWriteReg (int,unsigned int) ; 
 TYPE_3__ ym2612 ; 

void YM2612Write(unsigned int a, unsigned int v)
{
  v &= 0xff;  /* adjust to 8 bit bus */

  switch( a )
  {
    case 0:  /* address port 0 */
      ym2612.OPN.ST.address = v;
      break;

    case 2:  /* address port 1 */
      ym2612.OPN.ST.address = v | 0x100;
      break;

    default:  /* data port */
    {
      int addr = ym2612.OPN.ST.address; /* verified by Nemesis on real YM2612 */
      switch( addr & 0x1f0 )
      {
        case 0x20:  /* 0x20-0x2f Mode */
          switch( addr )
          {
            case 0x2a:  /* DAC data (ym2612) */
              ym2612.dacout = ((int)v - 0x80) << 6; /* convert to 14-bit output */
              break;
            case 0x2b:  /* DAC Sel  (ym2612) */
              /* b7 = dac enable */
              ym2612.dacen = v & 0x80;
              break;
            default:  /* OPN section */
              /* write register */
              OPNWriteMode(addr,v);
          }
          break;
        default:  /* 0x30-0xff OPN section */
          /* write register */
          OPNWriteReg(addr,v);
      }
      break;
    }
  }
}