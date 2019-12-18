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
struct pidfh {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  _PATH_MOUNTDPID ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pidfh* pidfile_open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 

__attribute__((used)) static void
restart_mountd(void)
{
	struct pidfh *pfh;
	pid_t mountdpid;

	pfh = pidfile_open(_PATH_MOUNTDPID, 0600, &mountdpid);
	if (pfh != NULL) {
		/* Mountd is not running. */
		pidfile_remove(pfh);
		return;
	}
	if (errno != EEXIST) {
		/* Cannot open pidfile for some reason. */
		return;
	}
	/* We have mountd(8) PID in mountdpid varible. */
	kill(mountdpid, SIGHUP);
}