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
 int /*<<< orphan*/  DEVTTY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fdopen (int,char*) ; 
 scalar_t__ iflag ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ttyinf ; 
 int /*<<< orphan*/ * ttyoutf ; 

int
tty_init(void)
{
	int ttyfd;

	if ((ttyfd = open(DEVTTY, O_RDWR)) >= 0) {
		if ((ttyoutf = fdopen(ttyfd, "w")) != NULL) {
			if ((ttyinf = fdopen(ttyfd, "r")) != NULL)
				return(0);
			(void)fclose(ttyoutf);
		}
		(void)close(ttyfd);
	}

	if (iflag) {
		paxwarn(1, "Fatal error, cannot open %s", DEVTTY);
		return(-1);
	}
	return(0);
}