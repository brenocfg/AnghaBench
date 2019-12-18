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
struct sysctl_req {int oldlen; int newlen; int /*<<< orphan*/  newptr; scalar_t__ oldptr; } ;
typedef  int /*<<< orphan*/  smallValue ;
typedef  int /*<<< orphan*/  bigValue ;

/* Variables and functions */
 int EPERM ; 
 int ERANGE ; 
 int SYSCTL_IN (struct sysctl_req*,void*,size_t) ; 
 int SYSCTL_OUT (struct sysctl_req*,...) ; 

int
sysctl_io_number(struct sysctl_req *req, long long bigValue, size_t valueSize, void *pValue, int *changed) {
	int		smallValue;
	int		error;

	if (changed) *changed = 0;

	/*
	 * Handle the various combinations of caller buffer size and
	 * data value size.  We are generous in the case where the
	 * caller has specified a 32-bit buffer but the value is 64-bit
	 * sized.
	 */

	/* 32 bit value expected or 32 bit buffer offered */
	if (((valueSize == sizeof(int)) ||
	    ((req->oldlen == sizeof(int)) && (valueSize == sizeof(long long))))
			&& (req->oldptr)) {
		smallValue = (int)bigValue;
		if ((long long)smallValue != bigValue)
			return(ERANGE);
		error = SYSCTL_OUT(req, &smallValue, sizeof(smallValue));
	} else {
		/* any other case is either size-equal or a bug */
		error = SYSCTL_OUT(req, &bigValue, valueSize);
	}
	/* error or nothing to set */
	if (error || !req->newptr)
		return(error);

	/* set request for constant */
	if (pValue == NULL)
		return(EPERM);

	/* set request needs to convert? */
	if ((req->newlen == sizeof(int)) && (valueSize == sizeof(long long))) {
		/* new value is 32 bits, upconvert to 64 bits */
		error = SYSCTL_IN(req, &smallValue, sizeof(smallValue));
		if (!error)
			*(long long *)pValue = (long long)smallValue;
	} else if ((req->newlen == sizeof(long long)) && (valueSize == sizeof(int))) {
		/* new value is 64 bits, downconvert to 32 bits and range check */
		error = SYSCTL_IN(req, &bigValue, sizeof(bigValue));
		if (!error) {
			smallValue = (int)bigValue;
			if ((long long)smallValue != bigValue)
				return(ERANGE);
			*(int *)pValue = smallValue;
		}
	} else {
		/* sizes match, just copy in */
		error = SYSCTL_IN(req, pValue, valueSize);
	}
	if (!error && changed)
		*changed = 1;
	return(error);
}