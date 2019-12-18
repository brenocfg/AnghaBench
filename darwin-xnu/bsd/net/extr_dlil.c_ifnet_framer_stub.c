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
typedef  scalar_t__ u_int32_t ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet {int /*<<< orphan*/  (* if_framer_legacy ) (struct ifnet*,struct mbuf**,struct sockaddr const*,char const*,char const*) ;} ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf**,struct sockaddr const*,char const*,char const*) ; 

errno_t
ifnet_framer_stub(struct ifnet *ifp, struct mbuf **m,
    const struct sockaddr *dest, const char *dest_linkaddr,
    const char *frame_type, u_int32_t *pre, u_int32_t *post)
{
	if (pre != NULL)
		*pre = 0;
	if (post != NULL)
		*post = 0;

	return (ifp->if_framer_legacy(ifp, m, dest, dest_linkaddr, frame_type));
}