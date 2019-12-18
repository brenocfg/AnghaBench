#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ pm_file ;

/* Variables and functions */
 int /*<<< orphan*/  Byteswap (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  DecodeSmd (unsigned char*,int) ; 
 int /*<<< orphan*/  EL_STATUS ; 
 int PAHW_MCD ; 
 int PicoAHW ; 
 unsigned char* PicoCartAlloc (int,int) ; 
 int /*<<< orphan*/  PicoCartLoadProgressCB (int) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 int pm_read (unsigned char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int PicoCartLoad(pm_file *f,unsigned char **prom,unsigned int *psize,int is_sms)
{
  unsigned char *rom;
  int size, bytes_read;

  if (f == NULL)
    return 1;

  size = f->size;
  if (size <= 0) return 1;
  size = (size+3)&~3; // Round up to a multiple of 4

  // Allocate space for the rom plus padding
  rom = PicoCartAlloc(size, is_sms);
  if (rom == NULL) {
    elprintf(EL_STATUS, "out of memory (wanted %i)", size);
    return 2;
  }

  if (PicoCartLoadProgressCB != NULL)
  {
    // read ROM in blocks, just for fun
    int ret;
    unsigned char *p = rom;
    bytes_read=0;
    do
    {
      int todo = size - bytes_read;
      if (todo > 256*1024) todo = 256*1024;
      ret = pm_read(p,todo,f);
      bytes_read += ret;
      p += ret;
      PicoCartLoadProgressCB(bytes_read * 100 / size);
    }
    while (ret > 0);
  }
  else
    bytes_read = pm_read(rom,size,f); // Load up the rom
  if (bytes_read <= 0) {
    elprintf(EL_STATUS, "read failed");
    free(rom);
    return 3;
  }

  if (!is_sms)
  {
    // maybe we are loading MegaCD BIOS?
    if (!(PicoAHW & PAHW_MCD) && size == 0x20000 && (!strncmp((char *)rom+0x124, "BOOT", 4) ||
         !strncmp((char *)rom+0x128, "BOOT", 4))) {
      PicoAHW |= PAHW_MCD;
    }

    // Check for SMD:
    if (size >= 0x4200 && (size&0x3fff) == 0x200 &&
        ((rom[0x2280] == 'S' && rom[0x280] == 'E') || (rom[0x280] == 'S' && rom[0x2281] == 'E'))) {
      elprintf(EL_STATUS, "SMD format detected.");
      DecodeSmd(rom,size); size-=0x200; // Decode and byteswap SMD
    }
    else Byteswap(rom, rom, size); // Just byteswap
  }
  else
  {
    if (size >= 0x4200 && (size&0x3fff) == 0x200) {
      elprintf(EL_STATUS, "SMD format detected.");
      // at least here it's not interleaved
      size -= 0x200;
      memmove(rom, rom + 0x200, size);
    }
  }

  if (prom)  *prom = rom;
  if (psize) *psize = size;

  return 0;
}