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
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* strerror (int) ; 
 size_t strlen (char*) ; 

int strerror_r(int err, char *buf, size_t buflen)
{
	char *msg = strerror(err);
	size_t l = strlen(msg);
	if (l >= buflen) {
		if (buflen) {
			memcpy(buf, msg, buflen-1);
			buf[buflen-1] = 0;
		}
		return ERANGE;
	}
	memcpy(buf, msg, l+1);
	return 0;
}