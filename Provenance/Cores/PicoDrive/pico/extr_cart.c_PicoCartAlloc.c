#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mcd_state ;

/* Variables and functions */
 unsigned char* plat_mmap (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rom_alloc_size ; 

__attribute__((used)) static unsigned char *PicoCartAlloc(int filesize, int is_sms)
{
  unsigned char *rom;

  if (is_sms) {
    // make size power of 2 for easier banking handling
    int s = 0, tmp = filesize;
    while ((tmp >>= 1) != 0)
      s++;
    if (filesize > (1 << s))
      s++;
    rom_alloc_size = 1 << s;
    // be sure we can cover all address space
    if (rom_alloc_size < 0x10000)
      rom_alloc_size = 0x10000;
  }
  else {
    // make alloc size at least sizeof(mcd_state),
    // in case we want to switch to CD mode
    if (filesize < sizeof(mcd_state))
      filesize = sizeof(mcd_state);

    // align to 512K for memhandlers
    rom_alloc_size = (filesize + 0x7ffff) & ~0x7ffff;
  }

  if (rom_alloc_size - filesize < 4)
    rom_alloc_size += 4; // padding for out-of-bound exec protection

  // Allocate space for the rom plus padding
  // use special address for 32x dynarec
  rom = plat_mmap(0x02000000, rom_alloc_size, 0, 0);
  return rom;
}