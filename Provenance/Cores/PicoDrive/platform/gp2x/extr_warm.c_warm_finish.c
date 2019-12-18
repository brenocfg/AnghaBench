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
typedef  int /*<<< orphan*/  unm ;
struct utsname {char* release; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int kernel_version ; 
 int /*<<< orphan*/  manual_rmmod (char*) ; 
 int /*<<< orphan*/  memset (struct utsname*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int system (char*) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 
 int warm_fd ; 

void warm_finish(void)
{
	char name[32], cmd[64];
	int ret;

	if (warm_fd < 0)
		return;

	close(warm_fd);
	warm_fd = -1;

	if (kernel_version < 0x26) {
		struct utsname unm;
		memset(&unm, 0, sizeof(unm));
		uname(&unm);
		snprintf(name, sizeof(name), "warm_%s", unm.release);
	}
	else
		strcpy(name, "warm");

	snprintf(cmd, sizeof(cmd), "/sbin/rmmod %s", name);
	ret = system(cmd);
	if (ret != 0) {
		fprintf(stderr, "system/rmmod failed: %d %d\n", ret, errno);
		manual_rmmod(name);
	}
}