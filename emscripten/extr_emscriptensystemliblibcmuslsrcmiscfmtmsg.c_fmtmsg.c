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
 long MM_CONSOLE ; 
 int MM_ERROR ; 
 int MM_HALT ; 
 int MM_INFO ; 
 int MM_NOCON ; 
 int MM_NOMSG ; 
 int MM_NOTOK ; 
 char* MM_NULLSEV ; 
 long MM_PRINT ; 
 int MM_WARNING ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  _strcolcmp (char* const,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dprintf (int,char*,char const*,char*,char*,char const*,char*,char const*,char*,char const*) ; 
 char* getenv (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 char* strchr (char*,char) ; 

int fmtmsg(long classification, const char *label, int severity,
           const char *text, const char *action, const char *tag)
{
	int ret = 0, i, consolefd, verb = 0;
	char *errstring = MM_NULLSEV, *cmsg = getenv("MSGVERB");
	char *const msgs[] = {
		"label", "severity", "text", "action", "tag", NULL
	};
	int cs;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);

	if (severity == MM_HALT) errstring = "HALT: ";
	else if (severity == MM_ERROR) errstring = "ERROR: ";
	else if (severity == MM_WARNING) errstring = "WARNING: ";
	else if (severity == MM_INFO) errstring = "INFO: ";

	if (classification & MM_CONSOLE) {
		consolefd = open("/dev/console", O_WRONLY);
		if (consolefd < 0) {
			ret = MM_NOCON;
		} else {
			if (dprintf(consolefd, "%s%s%s%s%s%s%s%s\n",
			            label?label:"", label?": ":"",
			            severity?errstring:"", text?text:"",
			            action?"\nTO FIX: ":"",
			            action?action:"", action?" ":"",
			            tag?tag:"" )<1)
				ret = MM_NOCON;
			close(consolefd);
		}
	}

	if (classification & MM_PRINT) {
		while (cmsg && cmsg[0]) {
			for(i=0; msgs[i]; i++) {
				if (!_strcolcmp(msgs[i], cmsg)) break;
			}
			if (msgs[i] == NULL) {
				//ignore MSGVERB-unrecognized component
				verb = 0xFF;
				break;
			} else {
				verb |= (1 << i);
				cmsg = strchr(cmsg, ':');
				if (cmsg) cmsg++;
			}
		}
		if (!verb) verb = 0xFF;
		if (dprintf(2, "%s%s%s%s%s%s%s%s\n",
		            (verb&1 && label) ? label : "",
		            (verb&1 && label) ? ": " : "",
		            (verb&2 && severity) ? errstring : "",
		            (verb&4 && text) ? text : "",
		            (verb&8 && action) ? "\nTO FIX: " : "",
		            (verb&8 && action) ? action : "",
		            (verb&8 && action) ? " " : "",
		            (verb&16 && tag) ? tag : "" ) < 1)
			ret |= MM_NOMSG;
	}
	if ((ret & (MM_NOCON|MM_NOMSG)) == (MM_NOCON|MM_NOMSG))
		ret = MM_NOTOK;

	pthread_setcancelstate(cs, 0);

	return ret;
}