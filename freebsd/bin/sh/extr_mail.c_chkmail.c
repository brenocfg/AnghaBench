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
struct stat {scalar_t__ st_mtime; scalar_t__ st_size; } ;
struct stackmark {int dummy; } ;

/* Variables and functions */
 scalar_t__* mailtime ; 
 int /*<<< orphan*/  mailval () ; 
 scalar_t__ mpathset () ; 
 int /*<<< orphan*/  mpathval () ; 
 int nmboxes ; 
 int /*<<< orphan*/  out2c (char) ; 
 int /*<<< orphan*/  out2str (char*) ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 char* strchrnul (char*,char) ; 
 char* stsavestr (int /*<<< orphan*/ ) ; 

void
chkmail(int silent)
{
	int i;
	char *mpath;
	char *p;
	char *msg;
	struct stackmark smark;
	struct stat statb;

	if (silent)
		nmboxes = 10;
	if (nmboxes == 0)
		return;
	setstackmark(&smark);
	mpath = stsavestr(mpathset()? mpathval() : mailval());
	for (i = 0 ; i < nmboxes ; i++) {
		p = mpath;
		if (*p == '\0')
			break;
		mpath = strchrnul(mpath, ':');
		if (*mpath != '\0') {
			*mpath++ = '\0';
			if (p == mpath - 1)
				continue;
		}
		msg = strchr(p, '%');
		if (msg != NULL)
			*msg++ = '\0';
#ifdef notdef /* this is what the System V shell claims to do (it lies) */
		if (stat(p, &statb) < 0)
			statb.st_mtime = 0;
		if (statb.st_mtime > mailtime[i] && ! silent) {
			out2str(msg? msg : "you have mail");
			out2c('\n');
		}
		mailtime[i] = statb.st_mtime;
#else /* this is what it should do */
		if (stat(p, &statb) < 0)
			statb.st_size = 0;
		if (statb.st_size > mailtime[i] && ! silent) {
			out2str(msg? msg : "you have mail");
			out2c('\n');
		}
		mailtime[i] = statb.st_size;
#endif
	}
	nmboxes = i;
	popstackmark(&smark);
}