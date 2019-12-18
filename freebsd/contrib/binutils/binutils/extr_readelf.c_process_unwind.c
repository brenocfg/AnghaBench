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
struct TYPE_2__ {int e_machine; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EM_IA_64 ; 
 int /*<<< orphan*/  EM_PARISC ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  do_unwind ; 
 TYPE_1__ elf_header ; 
 int /*<<< orphan*/  hppa_process_unwind ; 
 int /*<<< orphan*/  ia64_process_unwind ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
process_unwind (FILE *file)
{
  struct unwind_handler {
    int machtype;
    int (*handler)(FILE *file);
  } handlers[] = {
    { EM_IA_64, ia64_process_unwind },
    { EM_PARISC, hppa_process_unwind },
    { 0, 0 }
  };
  int i;

  if (!do_unwind)
    return 1;

  for (i = 0; handlers[i].handler != NULL; i++)
    if (elf_header.e_machine == handlers[i].machtype)
      return handlers[i].handler (file);

  printf (_("\nThere are no unwind sections in this file.\n"));
  return 1;
}