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
struct TYPE_2__ {scalar_t__ vma; } ;
typedef  TYPE_1__ reloc_data_type ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */

__attribute__((used)) static int
reloc_sort (const void *va, const void *vb)
{
  bfd_vma a = ((const reloc_data_type *) va)->vma;
  bfd_vma b = ((const reloc_data_type *) vb)->vma;

  return (a > b) ? 1 : ((a < b) ? -1 : 0);
}