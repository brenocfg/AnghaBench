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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static int
ia64_fbsd_pc_in_sigtramp (CORE_ADDR pc, char *func_name)
{
  uint64_t gwpage = 5ULL << 61;
  return (pc >= gwpage && pc < (gwpage + 8192)) ? 1 : 0;
}