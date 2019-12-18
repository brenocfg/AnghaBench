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
 int /*<<< orphan*/  carthw_chunks ; 
 int /*<<< orphan*/  carthw_ssf2_mem_setup ; 
 int /*<<< orphan*/  carthw_ssf2_state ; 
 int /*<<< orphan*/  carthw_ssf2_statef ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int* ssf2_banks ; 

void carthw_ssf2_startup(void)
{
	int i;

	elprintf(EL_STATUS, "SSF2 mapper startup");

	// default map
	for (i = 0; i < 8; i++)
		ssf2_banks[i] = i;

	PicoCartMemSetup  = carthw_ssf2_mem_setup;
	PicoLoadStateHook = carthw_ssf2_statef;
	carthw_chunks     = carthw_ssf2_state;
}