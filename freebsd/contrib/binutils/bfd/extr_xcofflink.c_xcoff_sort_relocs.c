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
struct internal_reloc {scalar_t__ r_vaddr; } ;

/* Variables and functions */

__attribute__((used)) static int
xcoff_sort_relocs (const void * p1, const void * p2)
{
  const struct internal_reloc *r1 = (const struct internal_reloc *) p1;
  const struct internal_reloc *r2 = (const struct internal_reloc *) p2;

  if (r1->r_vaddr > r2->r_vaddr)
    return 1;
  else if (r1->r_vaddr < r2->r_vaddr)
    return -1;
  else
    return 0;
}