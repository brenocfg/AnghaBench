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
struct servent {int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int getnum (char const*,size_t,int,void*,char*,char const*) ; 
 struct servent* getservbyname (char const*,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getport(const char *f, size_t l, bool local, void *r, const char *p)
{
	struct servent *sv;

	// XXX: Pass in the proto instead
	if ((sv = getservbyname(p, "tcp")) != NULL) {
		*(int *)r = ntohs(sv->s_port);
		return 0;
	}
	if ((sv = getservbyname(p, "udp")) != NULL) {
		*(int *)r = ntohs(sv->s_port);
		return 0;
	}

	return getnum(f, l, local, r, "service", p);
}