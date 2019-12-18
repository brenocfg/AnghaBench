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
 int /*<<< orphan*/  CHECK_READ_ONLY ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 scalar_t__ Devices_GetHostPath (int /*<<< orphan*/ ) ; 
 scalar_t__ Devices_MakeDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  host_path ; 

__attribute__((used)) static void Devices_H_MakeDirectory(void)
{
	if (devbug)
		Log_print("MKDIR Command");
	CHECK_READ_ONLY;

	if (Devices_GetHostPath(FALSE) == 0)
		return;

	if (Devices_MakeDirectory(host_path)) {
		CPU_regY = 1;
		CPU_ClrN;
	}
	else {
		CPU_regY = 144; /* device done error */
		CPU_SetN;
	}
}