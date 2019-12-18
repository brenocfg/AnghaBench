#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpname ;
struct TYPE_4__ {char* name; size_t nlen; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 int PAXPATHLEN ; 
 int add_name (char*,size_t,char*) ; 
 char* argv0 ; 
 size_t l_strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  ls_tty (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tty_prnt (char*,...) ; 
 scalar_t__ tty_read (char*,int) ; 

__attribute__((used)) static int
tty_rename(ARCHD *arcn)
{
	char tmpname[PAXPATHLEN+2];
	int res;

	/*
	 * prompt user for the replacement name for a file, keep trying until
	 * we get some reasonable input. Archives may have more than one file
	 * on them with the same name (from updates etc). We print verbose info
	 * on the file so the user knows what is up.
	 */
	tty_prnt("\nATTENTION: %s interactive file rename operation.\n", argv0);

	for (;;) {
		ls_tty(arcn);
		tty_prnt("Input new name, or a \".\" to keep the old name, ");
		tty_prnt("or a \"return\" to skip this file.\n");
		tty_prnt("Input > ");
		if (tty_read(tmpname, sizeof(tmpname)) < 0)
			return(-1);
		if (strcmp(tmpname, "..") == 0) {
			tty_prnt("Try again, illegal file name: ..\n");
			continue;
		}
		if (strlen(tmpname) > PAXPATHLEN) {
			tty_prnt("Try again, file name too long\n");
			continue;
		}
		break;
	}

	/*
	 * empty file name, skips this file. a "." leaves it alone
	 */
	if (tmpname[0] == '\0') {
		tty_prnt("Skipping file.\n");
		return(1);
	}
	if ((tmpname[0] == '.') && (tmpname[1] == '\0')) {
		tty_prnt("Processing continues, name unchanged.\n");
		return(0);
	}

	/*
	 * ok the name changed. We may run into links that point at this
	 * file later. we have to remember where the user sent the file
	 * in order to repair any links.
	 */
	tty_prnt("Processing continues, name changed to: %s\n", tmpname);
	res = add_name(arcn->name, arcn->nlen, tmpname);
	arcn->nlen = l_strncpy(arcn->name, tmpname, sizeof(arcn->name) - 1);
	arcn->name[arcn->nlen] = '\0';
	if (res < 0)
		return(-1);
	return(0);
}