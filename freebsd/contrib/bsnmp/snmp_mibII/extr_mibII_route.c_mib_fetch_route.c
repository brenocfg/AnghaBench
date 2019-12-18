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
typedef  scalar_t__ u_int ;
struct sroute {int dummy; } ;
typedef  struct sroute u_char ;
struct sockaddr {int dummy; } ;
struct rt_msghdr {scalar_t__ rtm_type; int rtm_flags; int /*<<< orphan*/  rtm_addrs; int /*<<< orphan*/  rtm_msglen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  NET_RT_DUMP ; 
 struct sroute* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sroute* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sroute*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sroute*) ; 
 scalar_t__ ROUTE_UPDATE_INTERVAL ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 int RTAX_MAX ; 
 size_t RTAX_NETMASK ; 
 int RTF_UP ; 
 scalar_t__ RTM_GET ; 
 int /*<<< orphan*/  free (struct sroute*) ; 
 scalar_t__ get_ticks () ; 
 int /*<<< orphan*/  mib_extract_addrs (int /*<<< orphan*/ ,struct sroute*,struct sockaddr**) ; 
 struct sroute* mib_fetch_rtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mib_sroute_process (struct rt_msghdr*,struct sockaddr*,struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ route_tick ; 
 scalar_t__ route_total ; 
 int /*<<< orphan*/  sroute_print (struct sroute*) ; 
 int /*<<< orphan*/  sroutes ; 
 scalar_t__ this_tick ; 

int
mib_fetch_route(void)
{
	u_char *rtab, *next;
	size_t len;
	struct sroute *r, *r1;
	struct rt_msghdr *rtm;
	struct sockaddr *addrs[RTAX_MAX];

	if (route_tick != 0 && route_tick + ROUTE_UPDATE_INTERVAL > this_tick)
		return (0);

	/*
	 * Remove all routes
	 */
	r = RB_MIN(sroutes, &sroutes);
	while (r != NULL) {
		r1 = RB_NEXT(sroutes, &sroutes, r);
		RB_REMOVE(sroutes, &sroutes, r);
		free(r);
		r = r1;
	}
	route_total = 0;

	if ((rtab = mib_fetch_rtab(AF_INET, NET_RT_DUMP, 0, &len)) == NULL)
		return (-1);

	next = rtab;
	for (next = rtab; next < rtab + len; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)(void *)next;
		if (rtm->rtm_type != RTM_GET ||
		    !(rtm->rtm_flags & RTF_UP))
			continue;
		mib_extract_addrs(rtm->rtm_addrs, (u_char *)(rtm + 1), addrs);


		mib_sroute_process(rtm, addrs[RTAX_GATEWAY], addrs[RTAX_DST],
		    addrs[RTAX_NETMASK]);
	}

#if 0
	u_int n = 0;
	r = RB_MIN(sroutes, &sroutes);
	while (r != NULL) {
		printf("%u: ", n++);
		sroute_print(r);
		printf("\n");
		r = RB_NEXT(sroutes, &sroutes, r);
	}
#endif
	free(rtab);
	route_tick = get_ticks();

	return (0);
}