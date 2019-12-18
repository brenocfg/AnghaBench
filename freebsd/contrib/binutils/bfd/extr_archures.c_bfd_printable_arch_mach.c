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
struct TYPE_3__ {char const* printable_name; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */
 TYPE_1__* bfd_lookup_arch (int,unsigned long) ; 

const char *
bfd_printable_arch_mach (enum bfd_architecture arch, unsigned long machine)
{
  const bfd_arch_info_type *ap = bfd_lookup_arch (arch, machine);

  if (ap)
    return ap->printable_name;
  return "UNKNOWN!";
}