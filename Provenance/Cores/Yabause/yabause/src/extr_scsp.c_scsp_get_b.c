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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int midflag; int ca; int sgc; int eg; int scieb; int scipd; int mcipd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSPLOG (char*,int) ; 
 TYPE_1__ scsp ; 
 int* scsp_ccr ; 
 int scsp_midi_in_read () ; 
 int scsp_midi_out_read () ; 

__attribute__((used)) static u8
scsp_get_b (u32 a)
{
  a &= 0x3F;

  if ((a != 0x09) && (a != 0x21))
    {
      SCSPLOG("r_b scsp : reg %.2X\n", a);
    }
//  if (a == 0x09) SCSPLOG("r_b scsp 09 = %.2X\n", ((scsp.slot[scsp.mslc].fcnt >> (SCSP_FREQ_LB + 12)) & 0x1) << 7);

  switch (a)
    {
    case 0x01: // VER/MVOL
      scsp_ccr[a ^ 3] &= 0x0F;
      break;

    case 0x04: // Midi flags register
      return scsp.midflag;

    case 0x05: // MIBUF
      return scsp_midi_in_read();

    case 0x07: // MOBUF
      return scsp_midi_out_read();

    case 0x08: // CA(highest 3 bits)
      return (scsp.ca >> 8);

    case 0x09: // CA(lowest bit)/SGC/EG
      return (scsp.ca & 0xE0) | (scsp.sgc << 5) | scsp.eg;

    case 0x1E: // SCIEB(high byte)
      return (scsp.scieb >> 8);

    case 0x1F: // SCIEB(low byte)
      return scsp.scieb;

    case 0x20: // SCIPD(high byte)
      return (scsp.scipd >> 8);

    case 0x21: // SCIPD(low byte)
      return scsp.scipd;

    case 0x2C: // MCIPD(high byte)
      return (scsp.mcipd >> 8);

    case 0x2D: // MCIPD(low byte)
      return scsp.mcipd;
    }

  return scsp_ccr[a ^ 3];
}