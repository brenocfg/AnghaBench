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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  display_ptable_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  get_cr3 () ; 
 int /*<<< orphan*/  get_pde (int) ; 
 int /*<<< orphan*/  get_pte (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isspace (char) ; 
 int parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  pdbr ; 
 int /*<<< orphan*/  printf_filtered (char*,unsigned long long) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
go32_pte_for_address (char *arg, int from_tty)
{
  CORE_ADDR addr = 0, i;

  if (arg && *arg)
    {
      while (*arg && isspace(*arg))
	arg++;

      if (*arg)
	addr = parse_and_eval_address (arg);
    }
  if (!addr)
    error_no_arg ("linear address");

  pdbr = get_cr3 ();
  if (!pdbr)
    puts_filtered ("Access to Page Tables is not supported on this system.\n");
  else
    {
      int pde_idx = (addr >> 22) & 0x3ff;
      int pte_idx = (addr >> 12) & 0x3ff;
      unsigned offs = addr & 0xfff;

      printf_filtered ("Page Table entry for address 0x%llx:\n",
		       (unsigned long long)addr);
      display_ptable_entry (get_pte (get_pde (pde_idx), pte_idx), 0, 1, offs);
    }
}