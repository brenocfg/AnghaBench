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
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  di ; 
 int /*<<< orphan*/  host_dasm_init () ; 
 int /*<<< orphan*/  init_done ; 
 char* lookup_name (scalar_t__) ; 
 scalar_t__ print_insn_func (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void host_dasm(void *addr, int len)
{
  bfd_vma vma_end, vma = (bfd_vma)(long)addr;
  const char *name;

  if (!init_done)
    host_dasm_init();

  vma_end = vma + len;
  while (vma < vma_end) {
    name = lookup_name(vma);
    if (name != NULL)
      printf("%s:\n", name);

    printf("   %08lx ", (long)vma);
    vma += print_insn_func(vma, &di);
    printf("\n");
  }
}