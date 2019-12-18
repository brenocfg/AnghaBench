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
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ *,int,unsigned long) ; 
 TYPE_1__* ecoff_backend (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_ecoff_set_arch_mach (bfd *abfd,
			  enum bfd_architecture arch,
			  unsigned long machine)
{
  bfd_default_set_arch_mach (abfd, arch, machine);
  return arch == ecoff_backend (abfd)->arch;
}