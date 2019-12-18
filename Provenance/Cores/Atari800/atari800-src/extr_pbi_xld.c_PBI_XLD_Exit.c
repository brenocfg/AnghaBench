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
 void* FALSE ; 
 void* PBI_XLD_enabled ; 
 void* PBI_XLD_v_enabled ; 
 int /*<<< orphan*/  diskrom ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  voicerom ; 
 void* xld_d_enabled ; 

void PBI_XLD_Exit(void)
{
	if (xld_d_enabled) {
		free(diskrom);
		xld_d_enabled = FALSE;
	}
	if (PBI_XLD_v_enabled) {
		free(voicerom);
		PBI_XLD_v_enabled = FALSE;
	}
	PBI_XLD_enabled = FALSE;
}