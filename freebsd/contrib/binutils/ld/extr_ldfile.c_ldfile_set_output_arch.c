#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
struct TYPE_3__ {int arch; int /*<<< orphan*/  printable_name; int /*<<< orphan*/  mach; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int bfd_arch_unknown ; 
 TYPE_1__* bfd_scan_arch (char const*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const*) ; 
 int ldfile_output_architecture ; 
 int /*<<< orphan*/  ldfile_output_machine ; 
 int /*<<< orphan*/  ldfile_output_machine_name ; 

void
ldfile_set_output_arch (const char *string, enum bfd_architecture defarch)
{
  const bfd_arch_info_type *arch = bfd_scan_arch (string);

  if (arch)
    {
      ldfile_output_architecture = arch->arch;
      ldfile_output_machine = arch->mach;
      ldfile_output_machine_name = arch->printable_name;
    }
  else if (defarch != bfd_arch_unknown)
    ldfile_output_architecture = defarch;
  else
    einfo (_("%P%F: cannot represent machine `%s'\n"), string);
}