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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ alphafbsd_sigtramp_end ; 
 scalar_t__ alphafbsd_sigtramp_start ; 

__attribute__((used)) static int
alphafbsd_pc_in_sigtramp (CORE_ADDR pc, char *func_name)
{
  return (pc >= alphafbsd_sigtramp_start && pc < alphafbsd_sigtramp_end);
}