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

/* Variables and functions */

unsigned long
bfd_elf_hash (const char *namearg)
{
  const unsigned char *name = (const unsigned char *) namearg;
  unsigned long h = 0;
  unsigned long g;
  int ch;

  while ((ch = *name++) != '\0')
    {
      h = (h << 4) + ch;
      if ((g = (h & 0xf0000000)) != 0)
	{
	  h ^= g >> 24;
	  /* The ELF ABI says `h &= ~g', but this is equivalent in
	     this case and on some machines one insn instead of two.  */
	  h ^= g;
	}
    }
  return h & 0xffffffff;
}