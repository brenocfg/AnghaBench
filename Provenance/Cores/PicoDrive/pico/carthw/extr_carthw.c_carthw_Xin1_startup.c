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
 int /*<<< orphan*/  EL_STATUS ; 
 int /*<<< orphan*/  PicoCartMemSetup ; 
 int /*<<< orphan*/  PicoLoadStateHook ; 
 int /*<<< orphan*/  PicoResetHook ; 
 int /*<<< orphan*/  carthw_Xin1_mem_setup ; 
 int /*<<< orphan*/  carthw_Xin1_reset ; 
 int /*<<< orphan*/  carthw_Xin1_state ; 
 int /*<<< orphan*/  carthw_Xin1_statef ; 
 int /*<<< orphan*/  carthw_chunks ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 

void carthw_Xin1_startup(void)
{
	elprintf(EL_STATUS, "X-in-1 mapper startup");

	PicoCartMemSetup  = carthw_Xin1_mem_setup;
	PicoResetHook     = carthw_Xin1_reset;
	PicoLoadStateHook = carthw_Xin1_statef;
	carthw_chunks     = carthw_Xin1_state;
}