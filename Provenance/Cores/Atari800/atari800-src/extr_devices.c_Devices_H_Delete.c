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
 scalar_t__ Devices_GetHostPath (int) ; 
 int /*<<< orphan*/  Devices_OpenDir (int /*<<< orphan*/ ) ; 
 scalar_t__ Devices_ReadDir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 scalar_t__ Util_unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  host_path ; 

__attribute__((used)) static void Devices_H_Delete(void)
{
	int num_deleted = 0;
	int num_failed = 0;
	int num_locked = 0;
	int readonly = FALSE;

	if (devbug)
		Log_print("DELETE Command");
	CHECK_READ_ONLY;

	if (Devices_GetHostPath(FALSE) == 0)
		return;

#ifdef DO_DIR
	if (!Devices_OpenDir(host_path)) {
		CPU_regY = 170; /* file not found */
		CPU_SetN;
		return;
	}
	while (Devices_ReadDir(host_path, NULL, NULL, &readonly, NULL, NULL))
#endif /* DO_DIR */
	{
		/* Check file write permission to mimic Atari
		   permission system: read-only ("locked") file
		   cannot be deleted. Modern systems have
		   a different permission for file deletion. */
		if (readonly)
			num_locked++;
		else
			if (Util_unlink(host_path) == 0)
				num_deleted++;
			else
				num_failed++;
	}

	if (devbug)
		Log_print("%d deleted, %d failed, %d locked",
		       num_deleted, num_failed, num_locked);

	if (num_locked) {
		CPU_regY = 167; /* file locked */
		CPU_SetN;
	}
	else if (num_failed != 0 || num_deleted == 0) {
		CPU_regY = 170; /* file not found */
		CPU_SetN;
	}
	else {
		CPU_regY = 1;
		CPU_ClrN;
	}
}