#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_5__ {scalar_t__ flavour; struct TYPE_5__ const* alternative_target; } ;
typedef  TYPE_1__ const bfd_target ;

/* Variables and functions */
 scalar_t__ bfd_target_elf_flavour ; 
 struct elf_backend_data* xvec_get_elf_backend_data (TYPE_1__ const*) ; 

__attribute__((used)) static void
bfd_elf_set_pagesize (const bfd_target *target, bfd_vma size,
		      int offset, const bfd_target *orig_target)
{
  if (target->flavour == bfd_target_elf_flavour)
    {
      const struct elf_backend_data *bed;

      bed = xvec_get_elf_backend_data (target);
      *((bfd_vma *) ((char *) bed + offset)) = size;
    }

  if (target->alternative_target
      && target->alternative_target != orig_target)
    bfd_elf_set_pagesize (target->alternative_target, size, offset,
			  orig_target);
}