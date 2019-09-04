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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char const,unsigned char const,unsigned char const,unsigned char const,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int strspn (char*,char*) ; 

const char *inet_ntop(int af, const void *restrict a0, char *restrict s, socklen_t l)
{
	const unsigned char *a = a0;
	int i, j, max, best;
	char buf[100];

	switch (af) {
	case AF_INET:
		if (snprintf(s, l, "%d.%d.%d.%d", a[0],a[1],a[2],a[3]) < l)
			return s;
		break;
	case AF_INET6:
		if (memcmp(a, "\0\0\0\0\0\0\0\0\0\0\377\377", 12))
			snprintf(buf, sizeof buf,
				"%x:%x:%x:%x:%x:%x:%x:%x",
				256*a[0]+a[1],256*a[2]+a[3],
				256*a[4]+a[5],256*a[6]+a[7],
				256*a[8]+a[9],256*a[10]+a[11],
				256*a[12]+a[13],256*a[14]+a[15]);
		else
			snprintf(buf, sizeof buf,
				"%x:%x:%x:%x:%x:%x:%d.%d.%d.%d",
				256*a[0]+a[1],256*a[2]+a[3],
				256*a[4]+a[5],256*a[6]+a[7],
				256*a[8]+a[9],256*a[10]+a[11],
				a[12],a[13],a[14],a[15]);
		/* Replace longest /(^0|:)[:0]{2,}/ with "::" */
		for (i=best=0, max=2; buf[i]; i++) {
			if (i && buf[i] != ':') continue;
			j = strspn(buf+i, ":0");
			if (j>max) best=i, max=j;
		}
		if (max>2) {
			buf[best] = buf[best+1] = ':';
			memmove(buf+best+2, buf+best+max, i-best-max+1);
		}
		if (strlen(buf) < l) {
			strcpy(s, buf);
			return s;
		}
		break;
	default:
		errno = EAFNOSUPPORT;
		return 0;
	}
	errno = ENOSPC;
	return 0;
}