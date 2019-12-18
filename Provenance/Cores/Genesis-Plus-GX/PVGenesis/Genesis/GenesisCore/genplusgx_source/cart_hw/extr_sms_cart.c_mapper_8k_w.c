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
struct TYPE_2__ {unsigned int pages; unsigned int* fcr; int /*<<< orphan*/ * rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHEATS_UPDATE () ; 
 TYPE_1__ slot ; 
 int /*<<< orphan*/ ** z80_readmap ; 

__attribute__((used)) static void mapper_8k_w(int offset, unsigned int data)
{
  int i;

  /* cartridge ROM page (8k) */
  uint8 page = data % slot.pages;
  
  /* Save frame control register data */
  slot.fcr[offset] = data;

  /* 4 x 8k banks */
  switch (offset & 3)
  {
    case 0: /* cartridge ROM bank (8k) at $8000-$9FFF */
    {
      for (i = 0x20; i < 0x28; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 13) | ((i & 0x07) << 10)];
      }
      break;
    }
    
    case 1: /* cartridge ROM bank (8k) at $A000-$BFFF */
    {
      for (i = 0x28; i < 0x30; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 13) | ((i & 0x07) << 10)];
      }
      break;
    }
    
    case 2: /* cartridge ROM bank (8k) at $4000-$5FFF */
    {
      for (i = 0x10; i < 0x18; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 13) | ((i & 0x07) << 10)];
      }
      break;
    }
    
    case 3: /* cartridge ROM bank (8k) at $6000-$7FFF */
    {
      for (i = 0x18; i < 0x20; i++)
      {
        z80_readmap[i] = &slot.rom[(page << 13) | ((i & 0x07) << 10)];
      }
      break;
    }
  }

#ifdef CHEATS_UPDATE
  /* update ROM patches when banking has changed */
  CHEATS_UPDATE();
#endif
}