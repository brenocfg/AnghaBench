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
 size_t PATH_MAX ; 
 scalar_t__ addr_last ; 
 char* getenv (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  quit (int) ; 
 int /*<<< orphan*/  sigactive ; 
 int sigflags ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ write_file (char*,char*,int,scalar_t__) ; 

void
handle_hup(int signo)
{
	char *hup = NULL;		/* hup filename */
	char *s;
	char ed_hup[] = "ed.hup";
	size_t n;

	if (!sigactive)
		quit(1);
	sigflags &= ~(1 << (signo - 1));
	if (addr_last && write_file(ed_hup, "w", 1, addr_last) < 0 &&
	    (s = getenv("HOME")) != NULL &&
	    (n = strlen(s)) + 8 <= PATH_MAX &&	/* "ed.hup" + '/' */
	    (hup = (char *) malloc(n + 10)) != NULL) {
		strcpy(hup, s);
		if (hup[n - 1] != '/')
			hup[n] = '/', hup[n+1] = '\0';
		strcat(hup, "ed.hup");
		write_file(hup, "w", 1, addr_last);
	}
	quit(2);
}