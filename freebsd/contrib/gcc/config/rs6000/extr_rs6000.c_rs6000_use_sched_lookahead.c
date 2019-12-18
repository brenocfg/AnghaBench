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

/* Variables and functions */
 scalar_t__ CPU_PPC8540 ; 
 scalar_t__ rs6000_cpu_attr ; 

__attribute__((used)) static int
rs6000_use_sched_lookahead (void)
{
  if (rs6000_cpu_attr == CPU_PPC8540)
    return 4;
  return 0;
}