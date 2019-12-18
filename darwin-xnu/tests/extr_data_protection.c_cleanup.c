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
 int /*<<< orphan*/  TEMP_DIR_TEMPLATE ; 
 int /*<<< orphan*/  TEST_PASSCODE ; 
 int /*<<< orphan*/  T_LOG (char*,...) ; 
 scalar_t__ clear_passcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ g_dir_fd ; 
 scalar_t__* g_dirpath ; 
 scalar_t__ g_fd ; 
 scalar_t__* g_filepath ; 
 scalar_t__ g_passcode_set ; 
 scalar_t__ g_subdir_fd ; 
 scalar_t__* g_subdirpath ; 
 scalar_t__* g_test_tempdir ; 
 int /*<<< orphan*/  rmdir (scalar_t__*) ; 
 scalar_t__ strcmp (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (scalar_t__*) ; 
 scalar_t__ unlock_device (int /*<<< orphan*/ ) ; 

void
cleanup(void) {
	T_LOG("Cleaning up…");

	if(g_subdir_fd >= 0) {
		T_LOG("Cleanup: closing fd %d", g_subdir_fd);
		close(g_subdir_fd);
	}

	if(g_subdirpath[0]) {
		T_LOG("Cleanup: removing %s", g_subdirpath);
		rmdir(g_subdirpath);
	}

	if(g_fd >= 0) {
		T_LOG("Cleanup: closing fd %d", g_fd);
		close(g_fd);
	}

	if(g_filepath[0]) {
		T_LOG("Cleanup: removing %s", g_filepath);
		unlink(g_filepath);
	}

	if(g_dir_fd >= 0) {
		T_LOG("Cleanup: closing fd %d", g_dir_fd);
		close(g_dir_fd);
	}

	if(g_dirpath[0]) {
		T_LOG("Cleanup: removing %s", g_dirpath);
		rmdir(g_dirpath);
	}

	if(strcmp(g_test_tempdir, TEMP_DIR_TEMPLATE)) {
		T_LOG("Cleanup: removing %s", g_test_tempdir);
		rmdir(g_test_tempdir);
	}

	if(g_passcode_set) {
		T_LOG("Cleanup: unlocking device");
		if(unlock_device(TEST_PASSCODE)) {
			T_LOG("Warning: failed to unlock device in cleanup");
		}

		T_LOG("Cleanup: clearing passcode");
		if(clear_passcode(TEST_PASSCODE)) {
			T_LOG("Warning: failed to clear passcode in cleanup");
		}
	}
}