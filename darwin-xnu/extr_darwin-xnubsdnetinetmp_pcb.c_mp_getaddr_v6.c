#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_3__ {struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct mptses {TYPE_2__ __mpte_dst_v6; TYPE_1__ __mpte_src_v6; } ;
typedef  int /*<<< orphan*/  in_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int ENOBUFS ; 
 struct sockaddr* in6_sockaddr (int /*<<< orphan*/ ,struct in6_addr*) ; 
 struct mptses* mpsotompte (struct socket*) ; 

__attribute__((used)) static int
mp_getaddr_v6(struct socket *mp_so, struct sockaddr **nam, boolean_t peer)
{
	struct mptses *mpte = mpsotompte(mp_so);
	struct in6_addr addr;
	in_port_t port;

	if (!peer) {
		port = mpte->__mpte_src_v6.sin6_port;
		addr = mpte->__mpte_src_v6.sin6_addr;
	} else {
		port = mpte->__mpte_dst_v6.sin6_port;
		addr = mpte->__mpte_dst_v6.sin6_addr;
	}

	*nam = in6_sockaddr(port, &addr);
	if (*nam == NULL)
		return (ENOBUFS);

	return (0);
}