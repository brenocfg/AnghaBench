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
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  hostname ; 
 int hostnamelen ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int
bsd_hostname(char * buf, int bufsize, int * len)
{
	/*
	 * "hostname" is null-terminated, and "hostnamelen" is equivalent to strlen(hostname).
	 */
	if (hostnamelen < bufsize) {
		strlcpy(buf, hostname, bufsize);
		*len = hostnamelen;
		return 0;
	} else {
		return ENAMETOOLONG;
	}
}