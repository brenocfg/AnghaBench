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
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  write_pc_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
write_pc (CORE_ADDR pc)
{
  write_pc_pid (pc, inferior_ptid);
}