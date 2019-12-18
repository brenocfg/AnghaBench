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
 int /*<<< orphan*/  Atari800_Exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_save_on_exit ; 
 int /*<<< orphan*/  FALSE ; 

void Atari800_ErrExit(void)
{
	CFG_save_on_exit = FALSE; /* avoid saving the config */
	Atari800_Exit(FALSE);
}