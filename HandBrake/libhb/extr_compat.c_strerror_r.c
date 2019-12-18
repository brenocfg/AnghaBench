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
 int EINVAL ; 
 int ERANGE ; 
 int ERRSTR_LEN ; 
 scalar_t__ snprintf (char*,size_t,char*,...) ; 

int strerror_r(int errnum, char *strerrbuf, size_t buflen)
{
    int ret = 0;
    char errstr[ERRSTR_LEN];

    if (strerrbuf == NULL || buflen == 0)
    {
        ret = ERANGE;
        goto done;
    }

    if(snprintf(errstr, ERRSTR_LEN - 1, "unknown error %d", errnum) < 0)
    {
        ret = EINVAL;
        goto done;
    }

    if (snprintf(strerrbuf, buflen, errstr) < 0)
    {
        ret = EINVAL;
        goto done;
    }

done:
    return ret;
}