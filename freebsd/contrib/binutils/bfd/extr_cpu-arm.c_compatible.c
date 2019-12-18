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
struct TYPE_5__ {scalar_t__ arch; scalar_t__ mach; scalar_t__ the_default; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */

__attribute__((used)) static const bfd_arch_info_type *
compatible (const bfd_arch_info_type *a, const bfd_arch_info_type *b)
{
  /* If a & b are for different architecture we can do nothing.  */
  if (a->arch != b->arch)
      return NULL;

  /* If a & b are for the same machine then all is well.  */
  if (a->mach == b->mach)
    return a;

  /* Otherwise if either a or b is the 'default' machine
     then it can be polymorphed into the other.  */
  if (a->the_default)
    return b;

  if (b->the_default)
    return a;

  /* So far all newer ARM architecture cores are
     supersets of previous cores.  */
  if (a->mach < b->mach)
    return b;
  else if (a->mach > b->mach)
    return a;

  /* Never reached!  */
  return NULL;
}