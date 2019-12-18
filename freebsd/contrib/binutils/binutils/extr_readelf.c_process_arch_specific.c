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
#define  EM_ARM 131 
#define  EM_MIPS 130 
#define  EM_MIPS_RS3_LE 129 
#define  EM_PPC 128 
 int /*<<< orphan*/  do_arch ; 
 TYPE_1__ elf_header ; 
 int process_arm_specific (int /*<<< orphan*/ *) ; 
 int process_mips_specific (int /*<<< orphan*/ *) ; 
 int process_power_specific (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
process_arch_specific (FILE *file)
{
  if (! do_arch)
    return 1;

  switch (elf_header.e_machine)
    {
    case EM_ARM:
      return process_arm_specific (file);
    case EM_MIPS:
    case EM_MIPS_RS3_LE:
      return process_mips_specific (file);
      break;
    case EM_PPC:
      return process_power_specific (file);
      break;
    default:
      break;
    }
  return 1;
}