#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct rtentry {int dummy; } ;
struct TYPE_2__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  bzero (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_str4 (struct rtentry*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_str6 (struct rtentry*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
rt_str(struct rtentry *rt, char *ds, uint32_t dslen, char *gs, uint32_t gslen)
{
	switch (rt_key(rt)->sa_family) {
	case AF_INET:
		rt_str4(rt, ds, dslen, gs, gslen);
		break;
#if INET6
	case AF_INET6:
		rt_str6(rt, ds, dslen, gs, gslen);
		break;
#endif /* INET6 */
	default:
		if (ds != NULL)
			bzero(ds, dslen);
		if (gs != NULL)
			bzero(gs, gslen);
		break;
	}
}