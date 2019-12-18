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
struct bfd_elf_version_expr {int dummy; } ;
struct TYPE_2__ {struct bfd_elf_version_expr* (* new_vers_pattern ) (struct bfd_elf_version_expr*) ;} ;

/* Variables and functions */
 TYPE_1__* ld_emulation ; 
 struct bfd_elf_version_expr* stub1 (struct bfd_elf_version_expr*) ; 

struct bfd_elf_version_expr *
ldemul_new_vers_pattern (struct bfd_elf_version_expr *entry)
{
  if (ld_emulation->new_vers_pattern)
    entry = (*ld_emulation->new_vers_pattern) (entry);
  return entry;
}