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
struct sockaddr_in6 {int dummy; } ;
struct rtentry {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct flowadv {int dummy; } ;

/* Variables and functions */
 int nd6_output_list (struct ifnet*,struct ifnet*,struct mbuf*,struct sockaddr_in6*,struct rtentry*,struct flowadv*) ; 

int
nd6_output(struct ifnet *ifp, struct ifnet *origifp, struct mbuf *m0,
    struct sockaddr_in6 *dst, struct rtentry *hint0, struct flowadv *adv)
{
	return nd6_output_list(ifp, origifp, m0, dst, hint0, adv);
}