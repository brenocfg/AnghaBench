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
 int /*<<< orphan*/  carthw_pier_statef () ; 
 int pier_dump_prot ; 
 int* pier_regs ; 

__attribute__((used)) static void carthw_pier_reset(void)
{
  pier_regs[0] = 1;
  pier_regs[1] = pier_regs[2] = pier_regs[3] = 0;
  pier_dump_prot = 3;
  carthw_pier_statef();
}