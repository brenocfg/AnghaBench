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
typedef  int /*<<< orphan*/  unshareline ;
typedef  int /*<<< orphan*/  shareline ;

/* Variables and functions */
 int BUFSIZ ; 
 int dotest () ; 
 int getpid () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  system (char*) ; 

int
main(int argc, char **argv)
{
	char shareline[BUFSIZ], unshareline[BUFSIZ];
	int rc;

	(void) snprintf(shareline, sizeof (shareline),
	    "mkdir /tmp/nfsv4test.%d ; share /tmp/nfsv4test.%d", getpid(),
	    getpid());
	(void) snprintf(unshareline, sizeof (unshareline),
	    "unshare /tmp/nfsv4test.%d ; rmdir /tmp/nfsv4test.%d", getpid(),
	    getpid());

	(void) system(shareline);
	rc = dotest();
	(void) system(unshareline);

	return (rc);
}