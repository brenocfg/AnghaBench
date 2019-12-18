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
struct rtentry {int rt_flags; } ;
typedef  scalar_t__ nstat_provider_cookie_t ;

/* Variables and functions */
 int RTF_UP ; 

__attribute__((used)) static int
nstat_route_gone(
	nstat_provider_cookie_t	cookie)
{
	struct rtentry		*rt = (struct rtentry*)cookie;
	return ((rt->rt_flags & RTF_UP) == 0) ? 1 : 0;
}