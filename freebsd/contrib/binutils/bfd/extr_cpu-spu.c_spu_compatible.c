#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ arch; } ;
typedef  TYPE_1__ bfd_arch_info_type ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
#define  bfd_arch_spu 128 
 TYPE_1__ const* bfd_default_compatible (TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static const bfd_arch_info_type *
spu_compatible (const bfd_arch_info_type *a, const bfd_arch_info_type *b)
{
  BFD_ASSERT (a->arch == bfd_arch_spu);
  switch (b->arch)
    {
    default:
      return NULL;
    case bfd_arch_spu:
      return bfd_default_compatible (a, b);
    }
  /*NOTREACHED*/
}