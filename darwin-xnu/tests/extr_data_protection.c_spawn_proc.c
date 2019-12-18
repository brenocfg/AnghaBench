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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_EXPECT_EQ (int,int /*<<< orphan*/ ,char*,char* const) ; 
 int /*<<< orphan*/  T_EXPECT_TRUE (int,char*,char* const) ; 
 int /*<<< orphan*/  T_LOG (char*,char* const,int) ; 
 int dt_launch_tool (int /*<<< orphan*/ *,char* const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_waitpid (int /*<<< orphan*/ ,int*,int*,int) ; 

int
spawn_proc(char * const command[]) {
	pid_t pid           = 0;
	int launch_tool_ret = 0;
	bool waitpid_ret    = true;
	int status          = 0;
	int signal          = 0;
	int timeout         = 30;

	launch_tool_ret = dt_launch_tool(&pid, command, false, NULL, NULL);
	T_EXPECT_EQ(launch_tool_ret, 0, "launch tool: %s", command[0]);
	if(launch_tool_ret != 0) {
		return 1;
	}

	waitpid_ret = dt_waitpid(pid, &status, &signal, timeout);
	T_EXPECT_TRUE(waitpid_ret, "%s should succeed", command[0]);
	if(waitpid_ret == false) {
		if(status != 0) {
			T_LOG("%s exited %d", command[0], status);
		}
		if(signal != 0) {
			T_LOG("%s received signal %d", command[0], signal);
		}
		return 1;
	}

	return 0;
}