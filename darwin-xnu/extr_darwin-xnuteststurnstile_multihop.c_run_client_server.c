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
typedef  int /*<<< orphan*/  dt_helper_t ;

/* Variables and functions */
 int /*<<< orphan*/  HELPER_TIMEOUT_SECS ; 
 int /*<<< orphan*/  LAUNCH_SYSTEM_DOMAIN ; 
 int /*<<< orphan*/  dt_fork_helper (char const*) ; 
 int /*<<< orphan*/  dt_launchd_helper_domain (char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_run_helpers (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_client_server(const char *server_name, const char *client_name)
{
	dt_helper_t helpers[] = {
		dt_launchd_helper_domain("com.apple.xnu.test.turnstile_multihop.plist",
				server_name, NULL, LAUNCH_SYSTEM_DOMAIN),
		dt_fork_helper(client_name)
	};
	dt_run_helpers(helpers, 2, HELPER_TIMEOUT_SECS);
}