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
 int PAHW_SMS ; 
 int PicoAHW ; 
 int /*<<< orphan*/  SekStepM68k () ; 
 int /*<<< orphan*/  z80_run_nr (int) ; 

void PDebugCPUStep(void)
{
  if (PicoAHW & PAHW_SMS)
    z80_run_nr(1);
  else
    SekStepM68k();
}