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
struct seg_descr {scalar_t__ stype; } ;

/* Variables and functions */
 scalar_t__ read_memory_region (unsigned long,void*,int) ; 

__attribute__((used)) static int
get_descriptor (unsigned long table_base, int idx, void *descr)
{
  unsigned long addr = table_base + idx * 8; /* 8 bytes per entry */

  if (read_memory_region (addr, descr, 8))
    return (int)((struct seg_descr *)descr)->stype;
  return -1;
}