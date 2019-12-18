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
 int Devices_RemoveDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  host_path ; 

__attribute__((used)) static void Devices_H_RemoveDirectory(void)
{
	if (devbug)
		Log_print("RMDIR Command");
	CHECK_READ_ONLY;

	if (Devices_GetHostPath(FALSE) == 0)
		return;

	CPU_regY = Devices_RemoveDirectory(host_path);
	if (CPU_regY >= 128)
		CPU_SetN;
	else
		CPU_ClrN;
}