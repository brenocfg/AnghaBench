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
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  DBG_APRINT (char*) ; 

void RDevice_INIT(void)
{
  DBG_APRINT("R*: INIT");
  CPU_regA = 1;
  CPU_regY = 1;
  CPU_ClrN;
}