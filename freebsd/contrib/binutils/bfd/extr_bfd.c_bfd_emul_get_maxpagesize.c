#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_5__ {scalar_t__ flavour; } ;
typedef  TYPE_1__ bfd_target ;
struct TYPE_6__ {int /*<<< orphan*/  maxpagesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* bfd_find_target (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 TYPE_2__* xvec_get_elf_backend_data (TYPE_1__ const*) ; 

bfd_vma
bfd_emul_get_maxpagesize (const char *emul)
{
  const bfd_target *target;

  target = bfd_find_target (emul, NULL);
  if (target != NULL
      && target->flavour == bfd_target_elf_flavour)
    return xvec_get_elf_backend_data (target)->maxpagesize;

  abort ();
  return 0;
}