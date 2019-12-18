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
typedef  int uint8 ;
typedef  int uint32 ;
struct TYPE_2__ {int* sram; } ;

/* Variables and functions */
 TYPE_1__ sram ; 

__attribute__((used)) static uint32 mapper_smw_64_r(uint32 address)
{
  /* internal registers (saved to backup RAM) */
  switch ((address >> 16) & 0x03)
  {
    case 0x02:  /* $66xxxx */
    {
      switch ((address >> 1) & 7)
      {
        case 0x00:  return sram.sram[0x06];
        case 0x01:  return sram.sram[0x06] + 1;
        case 0x02:  return sram.sram[0x07];
        case 0x03:  return sram.sram[0x07] + 1;
        case 0x04:  return sram.sram[0x08];
        case 0x05:  return sram.sram[0x08] + 1;
        case 0x06:  return sram.sram[0x08] + 2;
        case 0x07:  return sram.sram[0x08] + 3;
      }
    }

    case 0x03:  /* $67xxxx */
    {
      uint8 data = (sram.sram[0x02] & 0x80) ? ((sram.sram[0x05] & 0x40) ? (sram.sram[0x03] & sram.sram[0x04]) : (sram.sram[0x03] ^ 0xFF)) : 0x00;

      if (address & 2)
      {
        /* $670003 */
        data &= 0x7f;
      }
      else
      {
        /* $66xxxx data registers update */
        if (sram.sram[0x05] & 0x80)
        {
          if (sram.sram[0x05] & 0x20)
          {
            /* update $660009-$66000f data register */
            sram.sram[0x08] = (sram.sram[0x04] << 2) & 0xFC;
          }
          else
          {
            /* update $660001-$660003 data register */
            sram.sram[0x06] = (sram.sram[0x01] ^ (sram.sram[0x03] << 1)) & 0xFE;
          }
        }
      }

      return data;
    }

    default:  /* 64xxxx-$65xxxx */
    {
      return 0x00;
    }
  }
}