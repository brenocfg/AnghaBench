#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_8__ {int dotMask; int stampShift; int mapShift; int bufferOffset; int bufferStart; int cycles; int cyclesPerLine; int /*<<< orphan*/ * mapPtr; int /*<<< orphan*/ * tracePtr; } ;
struct TYPE_7__ {TYPE_2__* regs; scalar_t__ word_ram_2M; } ;
struct TYPE_5__ {int l; int h; } ;
struct TYPE_6__ {int w; TYPE_1__ byte; } ;

/* Variables and functions */
 TYPE_4__ gfx ; 
 TYPE_3__ scd ; 

void gfx_start(unsigned int base, int cycles)
{
  /* make sure 2M mode is enabled */
  if (!(scd.regs[0x02>>1].byte.l & 0x04))
  {
    uint32 mask;
    
    /* trace vector pointer */
    gfx.tracePtr = (uint16 *)(scd.word_ram_2M + ((base << 2) & 0x3fff8));

    /* stamps & stamp map size */
    switch ((scd.regs[0x58>>1].byte.l >> 1) & 0x03)
    {
      case 0:
        gfx.dotMask = 0x07ffff;   /* 256x256 dots/map  */
        gfx.stampShift = 11 + 4;  /* 16x16 dots/stamps */
        gfx.mapShift = 4;         /* 16x16 stamps/map  */
        mask = 0x3fe00;           /* 512 bytes/table   */
        break;

      case 1:
        gfx.dotMask = 0x07ffff;   /* 256x256 dots/map  */
        gfx.stampShift = 11 + 5;  /* 32x32 dots/stamps */
        gfx.mapShift = 3;         /* 8x8 stamps/map    */
        mask = 0x3ff80;           /* 128 bytes/table   */
        break;

      case 2:
        gfx.dotMask = 0x7fffff;   /* 4096*4096 dots/map */
        gfx.stampShift = 11 + 4;  /* 16x16 dots/stamps  */
        gfx.mapShift = 8;         /* 256x256 stamps/map */
        mask = 0x20000;           /* 131072 bytes/table */
        break;

      case 3:
        gfx.dotMask = 0x7fffff;   /* 4096*4096 dots/map */
        gfx.stampShift = 11 + 5;  /* 32x32 dots/stamps  */
        gfx.mapShift = 7;         /* 128x128 stamps/map */
        mask = 0x38000;           /* 32768 bytes/table  */
        break;
    }

    /* stamp map table base address */
    gfx.mapPtr = (uint16 *)(scd.word_ram_2M + ((scd.regs[0x5a>>1].w << 2) & mask));

    /* image buffer column offset (64 pixels/cell, minus 7 pixels to restart at cell beginning) */
    gfx.bufferOffset = (((scd.regs[0x5c>>1].byte.l & 0x1f) + 1) << 6) - 7;

    /* image buffer start index in dot units (2 pixels/byte) */
    gfx.bufferStart = (scd.regs[0x5e>>1].w << 3) & 0x7ffc0;

    /* add image buffer horizontal dot offset */
    gfx.bufferStart += (scd.regs[0x60>>1].byte.l & 0x3f);

    /* reset GFX chip cycle counter */
    gfx.cycles = cycles;

    /* update GFX chip timings (see AC3:Thunderhawk / Thunderstrike) */
    gfx.cyclesPerLine = 4 * 5 * scd.regs[0x62>>1].w; 

    /* start graphics operation */
    scd.regs[0x58>>1].byte.h = 0x80;
  }
}