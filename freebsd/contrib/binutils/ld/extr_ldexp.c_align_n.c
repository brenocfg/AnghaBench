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
typedef  int bfd_vma ;

/* Variables and functions */

__attribute__((used)) static bfd_vma
align_n (bfd_vma value, bfd_vma align)
{
  if (align <= 1)
    return value;

  value = (value + align - 1) / align;
  return value * align;
}