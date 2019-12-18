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
struct TYPE_2__ {int romsize; scalar_t__ rom; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 
 int strlen (char const*) ; 

__attribute__((used)) static int rom_strcmp(int rom_offset, const char *s1)
{
  int i, len = strlen(s1);
  const char *s_rom = (const char *)Pico.rom;
  if (rom_offset + len > Pico.romsize)
    return 0;
  for (i = 0; i < len; i++)
    if (s1[i] != s_rom[(i + rom_offset) ^ 1])
      return 1;
  return 0;
}