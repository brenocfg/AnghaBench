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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ fbsd_pc_in_sigtramp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mipsfbsd_sigtramp_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mipsfbsd_pc_in_sigtramp (CORE_ADDR pc, char *func_name)
{
  return (fbsd_pc_in_sigtramp (pc, func_name)
	  || mipsfbsd_sigtramp_offset (pc) >= 0);
}