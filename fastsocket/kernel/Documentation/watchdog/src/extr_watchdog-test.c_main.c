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
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  WDIOC_SETOPTIONS ; 
 int /*<<< orphan*/  WDIOS_DISABLECARD ; 
 int /*<<< orphan*/  WDIOS_ENABLECARD ; 
 int /*<<< orphan*/  exit (int) ; 
 int fd ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keep_alive () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 

int main(int argc, char *argv[])
{
    fd = open("/dev/watchdog", O_WRONLY);

    if (fd == -1) {
	fprintf(stderr, "Watchdog device not enabled.\n");
	fflush(stderr);
	exit(-1);
    }

    if (argc > 1) {
	if (!strncasecmp(argv[1], "-d", 2)) {
	    ioctl(fd, WDIOC_SETOPTIONS, WDIOS_DISABLECARD);
	    fprintf(stderr, "Watchdog card disabled.\n");
	    fflush(stderr);
	    exit(0);
	} else if (!strncasecmp(argv[1], "-e", 2)) {
	    ioctl(fd, WDIOC_SETOPTIONS, WDIOS_ENABLECARD);
	    fprintf(stderr, "Watchdog card enabled.\n");
	    fflush(stderr);
	    exit(0);
	} else {
	    fprintf(stderr, "-d to disable, -e to enable.\n");
	    fprintf(stderr, "run by itself to tick the card.\n");
	    fflush(stderr);
	    exit(0);
	}
    } else {
	fprintf(stderr, "Watchdog Ticking Away!\n");
	fflush(stderr);
    }

    while(1) {
	keep_alive();
	sleep(1);
    }
}