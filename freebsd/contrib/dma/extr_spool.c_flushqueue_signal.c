#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  spooldir; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SPOOL_FLUSHFILE ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

int
flushqueue_signal(void)
{
        char *flushfn = NULL;
	int fd;

        if (asprintf(&flushfn, "%s/%s", config.spooldir, SPOOL_FLUSHFILE) < 0)
		return (-1);
	fd = open(flushfn, O_CREAT|O_WRONLY|O_TRUNC, 0660);
	free(flushfn);
	if (fd < 0) {
		syslog(LOG_ERR, "could not open flush file: %m");
		return (-1);
	}
        close(fd);
	return (0);
}