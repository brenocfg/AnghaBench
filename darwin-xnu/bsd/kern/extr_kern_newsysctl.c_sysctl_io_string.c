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
struct sysctl_req {int oldlen; size_t newlen; int /*<<< orphan*/  newptr; scalar_t__ oldptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int SYSCTL_IN (struct sysctl_req*,char*,size_t) ; 
 int SYSCTL_OUT (struct sysctl_req*,char*,int) ; 
 int strlen (char*) ; 

int
sysctl_io_string(struct sysctl_req *req, char *pValue, size_t valueSize, int trunc, int *changed)
{
	int error;

	if (changed) *changed = 0;

	if (trunc && req->oldptr && req->oldlen && (req->oldlen<strlen(pValue) + 1)) {
		/* If trunc != 0, if you give it a too small (but larger than
		 * 0 bytes) buffer, instead of returning ENOMEM, it truncates the
		 * returned string to the buffer size.  This preserves the semantics
		 * of some library routines implemented via sysctl, which truncate
		 * their returned data, rather than simply returning an error. The
		 * returned string is always NUL terminated. */
		error = SYSCTL_OUT(req, pValue, req->oldlen-1);
		if (!error) {
			char c = 0;
			error = SYSCTL_OUT(req, &c, 1);
		}
	} else {
		/* Copy string out */
		error = SYSCTL_OUT(req, pValue, strlen(pValue) + 1);
	}

	/* error or no new value */
	if (error || !req->newptr)
		return(error);

	/* attempt to set read-only value */
	if (valueSize == 0)
		return(EPERM);

	/* make sure there's room for the new string */
	if (req->newlen >= valueSize)
		return(EINVAL);

	/* copy the string in and force NUL termination */
	error = SYSCTL_IN(req, pValue, req->newlen);
	pValue[req->newlen] = '\0';

	if (!error && changed)
		*changed = 1;
	return(error);
}