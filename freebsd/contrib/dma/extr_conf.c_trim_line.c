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
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
trim_line(char *line)
{
	size_t linelen;
	char *p;

	if ((p = strchr(line, '\n')))
		*p = (char)0;

	/* Escape leading dot in every case */
	linelen = strlen(line);
	if (line[0] == '.') {
		if ((linelen + 2) > 1000) {
			syslog(LOG_CRIT, "Cannot escape leading dot.  Buffer overflow");
			exit(EX_DATAERR);
		}
		memmove((line + 1), line, (linelen + 1));
		line[0] = '.';
	}
}