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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct in_ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_setdstifaddr_info (struct mbuf*,int /*<<< orphan*/ ,struct in_ifaddr*) ; 
 struct mbuf* mbuf_nextpkt (struct mbuf*) ; 

__attribute__((used)) static void
ip_input_setdst_chain(struct mbuf *m, uint32_t ifindex, struct in_ifaddr *ia)
{
	struct mbuf *tmp_mbuf = m;

	while (tmp_mbuf) {
		ip_setdstifaddr_info(tmp_mbuf, ifindex, ia);
		tmp_mbuf = mbuf_nextpkt(tmp_mbuf);
	}
}