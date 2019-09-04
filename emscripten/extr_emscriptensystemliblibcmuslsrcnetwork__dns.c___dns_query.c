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
 int AF_INET ; 
 int AF_INET6 ; 
 int PTR_MAX ; 
 int RR_A ; 
 int RR_AAAA ; 
 int RR_PTR ; 
 int __dns_doqueries (unsigned char*,void const*,int*,int) ; 
 int /*<<< orphan*/  mkptr4 (char*,void const*) ; 
 int /*<<< orphan*/  mkptr6 (char*,void const*) ; 

int __dns_query(unsigned char *r, const void *a, int family, int ptr)
{
	char buf[PTR_MAX];
	int rr[2], rrcnt = 1;

	if (ptr) {
		if (family == AF_INET6) mkptr6(buf, a);
		else mkptr4(buf, a);
		rr[0] = RR_PTR;
		a = buf;
	} else if (family == AF_INET6) {
		rr[0] = RR_AAAA;
	} else {
		rr[0] = RR_A;
		if (family != AF_INET) rr[rrcnt++] = RR_AAAA;
	}

	return __dns_doqueries(r, a, rr, rrcnt);
}