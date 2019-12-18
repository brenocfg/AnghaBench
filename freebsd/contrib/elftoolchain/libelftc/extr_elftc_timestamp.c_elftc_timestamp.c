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
typedef  long long time_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 long long strtoll (char*,char**,int) ; 
 long long time (int /*<<< orphan*/ *) ; 

int
elftc_timestamp(time_t *timestamp)
{
	long long source_date_epoch;
	char *env, *eptr;

	if ((env = getenv("SOURCE_DATE_EPOCH")) != NULL) {
		errno = 0;
		source_date_epoch = strtoll(env, &eptr, 10);
		if (*eptr != '\0')
			errno = EINVAL;
		if (source_date_epoch < 0)
			errno = ERANGE;
		if (errno != 0)
			return (-1);
		*timestamp = source_date_epoch;
		return (0);
	}
	*timestamp = time(NULL);
	return (0);
}