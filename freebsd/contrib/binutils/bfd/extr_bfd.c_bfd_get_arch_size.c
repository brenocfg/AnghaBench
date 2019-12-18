#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* xvec; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_10__ {TYPE_2__* s; } ;
struct TYPE_8__ {int arch_size; } ;
struct TYPE_7__ {scalar_t__ flavour; } ;

/* Variables and functions */
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_4__* get_elf_backend_data (TYPE_3__*) ; 

int
bfd_get_arch_size (bfd *abfd)
{
  if (abfd->xvec->flavour == bfd_target_elf_flavour)
    return get_elf_backend_data (abfd)->s->arch_size;

  return -1;
}