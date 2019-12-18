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
 int /*<<< orphan*/  PicoCartUnloadHook ; 
 int /*<<< orphan*/  carthw_sprot_mem_setup ; 
 int /*<<< orphan*/  carthw_sprot_unload ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 

void carthw_sprot_startup(void)
{
  elprintf(EL_STATUS, "Prot emu startup");

  PicoCartMemSetup   = carthw_sprot_mem_setup;
  PicoCartUnloadHook = carthw_sprot_unload;
}