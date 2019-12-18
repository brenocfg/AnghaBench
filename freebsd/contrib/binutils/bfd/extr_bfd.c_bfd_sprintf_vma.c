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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* elf_backend_sprintf_vma ) (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf_vma (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void
bfd_sprintf_vma (bfd *abfd, char *buf, bfd_vma value)
{
  if (bfd_get_flavour (abfd) == bfd_target_elf_flavour)
    get_elf_backend_data (abfd)->elf_backend_sprintf_vma (abfd, buf, value);
  else
    sprintf_vma (buf, value);
}