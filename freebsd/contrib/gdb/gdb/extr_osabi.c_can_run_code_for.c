#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfd_arch_info {struct bfd_arch_info const* (* compatible ) (struct bfd_arch_info const*,struct bfd_arch_info const*) ;} ;

/* Variables and functions */
 struct bfd_arch_info const* stub1 (struct bfd_arch_info const*,struct bfd_arch_info const*) ; 

__attribute__((used)) static int
can_run_code_for (const struct bfd_arch_info *a, const struct bfd_arch_info *b)
{
  /* BFD's 'A->compatible (A, B)' functions return zero if A and B are
     incompatible.  But if they are compatible, it returns the 'more
     featureful' of the two arches.  That is, if A can run code
     written for B, but B can't run code written for A, then it'll
     return A.

     struct bfd_arch_info objects are singletons: that is, there's
     supposed to be exactly one instance for a given machine.  So you
     can tell whether two are equivalent by comparing pointers.  */
  return (a == b || a->compatible (a, b) == a);
}