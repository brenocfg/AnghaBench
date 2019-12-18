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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * fd_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module ; 
 int /*<<< orphan*/ * ntpd_fd ; 
 int /*<<< orphan*/  ntpd_input ; 
 int /*<<< orphan*/  ntpd_sock ; 
 int /*<<< orphan*/  oid_ntpMIB ; 
 int open_socket () ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_index ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ntp_start(void)
{

	if (open_socket() != -1) {
		ntpd_fd = fd_select(ntpd_sock, ntpd_input, NULL, module);
		if (ntpd_fd == NULL) {
			syslog(LOG_ERR, "fd_select failed on ntpd socket: %m");
			return;
		}
	}
	reg_index = or_register(&oid_ntpMIB, "The MIB for NTP.", module);
}