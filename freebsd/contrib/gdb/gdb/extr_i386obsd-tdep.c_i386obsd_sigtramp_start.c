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
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ i386bsd_pc_in_sigtramp (int,int /*<<< orphan*/ *) ; 
 int i386bsd_sigtramp_start (int) ; 
 int i386obsd_page_size ; 

__attribute__((used)) static CORE_ADDR
i386obsd_sigtramp_start (CORE_ADDR pc)
{
  CORE_ADDR start_pc = (pc & ~(i386obsd_page_size - 1));

  if (i386bsd_pc_in_sigtramp (pc, NULL))
    return i386bsd_sigtramp_start (pc);

  return start_pc;
}