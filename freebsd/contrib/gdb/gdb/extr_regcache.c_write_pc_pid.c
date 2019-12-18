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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_WRITE_PC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 

void
write_pc_pid (CORE_ADDR pc, ptid_t ptid)
{
  ptid_t saved_inferior_ptid;

  /* In case ptid != inferior_ptid. */
  saved_inferior_ptid = inferior_ptid;
  inferior_ptid = ptid;

  TARGET_WRITE_PC (pc, ptid);

  inferior_ptid = saved_inferior_ptid;
}