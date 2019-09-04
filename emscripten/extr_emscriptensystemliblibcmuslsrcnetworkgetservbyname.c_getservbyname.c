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
struct servent {int dummy; } ;

/* Variables and functions */
 scalar_t__ getservbyname_r (char const*,char const*,struct servent*,void*,int,struct servent**) ; 

struct servent *getservbyname(const char *name, const char *prots)
{
	static struct servent se;
	static char *buf[2];
	struct servent *res;
	if (getservbyname_r(name, prots, &se, (void *)buf, sizeof buf, &res))
		return 0;
	return &se;
}