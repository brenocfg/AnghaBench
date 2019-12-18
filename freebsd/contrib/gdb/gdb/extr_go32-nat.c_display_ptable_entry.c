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
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
display_ptable_entry (unsigned long entry, int is_dir, int force, unsigned off)
{
  if ((entry & 1) != 0)
    {
      printf_filtered ("Base=0x%05lx000", entry >> 12);
      if ((entry & 0x100) && !is_dir)
	puts_filtered (" Global");
      if ((entry & 0x40) && !is_dir)
	puts_filtered (" Dirty");
      printf_filtered (" %sAcc.", (entry & 0x20) ? "" : "Not-");
      printf_filtered (" %sCached", (entry & 0x10) ? "" : "Not-");
      printf_filtered (" Write-%s", (entry & 8) ? "Thru" : "Back");
      printf_filtered (" %s", (entry & 4) ? "Usr" : "Sup");
      printf_filtered (" Read-%s", (entry & 2) ? "Write" : "Only");
      if (off)
	printf_filtered (" +0x%x", off);
      puts_filtered ("\n");
    }
  else if (force)
    printf_filtered ("Page%s not present or not supported; value=0x%lx.\n",
		     is_dir ? " Table" : "", entry >> 1);
}