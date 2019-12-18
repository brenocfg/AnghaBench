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
struct job {scalar_t__ used; int nprocs; TYPE_1__* ps; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {scalar_t__ pid; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,...) ; 
 struct job* getcurjob (struct job*) ; 
 scalar_t__ is_digit (char const) ; 
 scalar_t__ is_number (char const*) ; 
 struct job* jobtab ; 
 int njobs ; 
 int number (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct job *
getjob_nonotfound(const char *name)
{
	int jobno;
	struct job *found, *jp;
	size_t namelen;
	pid_t pid;
	int i;

	if (name == NULL) {
#if JOBS
		name = "%+";
#else
		error("No current job");
#endif
	}
	if (name[0] == '%') {
		if (is_digit(name[1])) {
			jobno = number(name + 1);
			if (jobno > 0 && jobno <= njobs
			 && jobtab[jobno - 1].used != 0)
				return &jobtab[jobno - 1];
#if JOBS
		} else if ((name[1] == '%' || name[1] == '+') &&
		    name[2] == '\0') {
			if ((jp = getcurjob(NULL)) == NULL)
				error("No current job");
			return (jp);
		} else if (name[1] == '-' && name[2] == '\0') {
			if ((jp = getcurjob(NULL)) == NULL ||
			    (jp = getcurjob(jp)) == NULL)
				error("No previous job");
			return (jp);
#endif
		} else if (name[1] == '?') {
			found = NULL;
			for (jp = jobtab, i = njobs ; --i >= 0 ; jp++) {
				if (jp->used && jp->nprocs > 0
				 && strstr(jp->ps[0].cmd, name + 2) != NULL) {
					if (found)
						error("%s: ambiguous", name);
					found = jp;
				}
			}
			if (found != NULL)
				return (found);
		} else {
			namelen = strlen(name);
			found = NULL;
			for (jp = jobtab, i = njobs ; --i >= 0 ; jp++) {
				if (jp->used && jp->nprocs > 0
				 && strncmp(jp->ps[0].cmd, name + 1,
				 namelen - 1) == 0) {
					if (found)
						error("%s: ambiguous", name);
					found = jp;
				}
			}
			if (found)
				return found;
		}
	} else if (is_number(name)) {
		pid = (pid_t)number(name);
		for (jp = jobtab, i = njobs ; --i >= 0 ; jp++) {
			if (jp->used && jp->nprocs > 0
			 && jp->ps[jp->nprocs - 1].pid == pid)
				return jp;
		}
	}
	return NULL;
}