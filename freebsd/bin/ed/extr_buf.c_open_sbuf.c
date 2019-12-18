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
 int ERR ; 
 int /*<<< orphan*/  close (int) ; 
 char* errmsg ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ isbinary ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 scalar_t__ newline_added ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfn ; 
 int /*<<< orphan*/ * sfp ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int umask (int) ; 

int
open_sbuf(void)
{
	int fd;
	int u;

	isbinary = newline_added = 0;
	u = umask(077);
	strcpy(sfn, "/tmp/ed.XXXXXX");
	if ((fd = mkstemp(sfn)) == -1 ||
	    (sfp = fdopen(fd, "w+")) == NULL) {
		if (fd != -1)
			close(fd);
		perror(sfn);
		errmsg = "cannot open temp file";
		umask(u);
		return ERR;
	}
	umask(u);
	return 0;
}