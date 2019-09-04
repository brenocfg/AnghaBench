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
struct rtentry {int rt_flags; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int sa_family; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  RN (struct rtentry*) ; 
 int RTF_CONDEMNED ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  in6_validate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_validate (int /*<<< orphan*/ ) ; 
 TYPE_1__* rt_key (struct rtentry*) ; 

boolean_t
rt_validate(struct rtentry *rt)
{
	RT_LOCK_ASSERT_HELD(rt);

	if ((rt->rt_flags & (RTF_UP | RTF_CONDEMNED)) == RTF_UP) {
		int af = rt_key(rt)->sa_family;

		if (af == AF_INET)
			(void) in_validate(RN(rt));
		else if (af == AF_INET6)
			(void) in6_validate(RN(rt));
	} else {
		rt = NULL;
	}

	return (rt != NULL);
}