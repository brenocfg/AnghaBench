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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {int /*<<< orphan*/  m_flags; TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_PROTO1 ; 
 scalar_t__ ifnet_output_raw (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  ifnet_stat_increment_out (struct ifnet*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bstp_enqueue(struct ifnet *dst_ifp, struct mbuf *m)
{
	errno_t error = 0;
	u_int32_t len = m->m_pkthdr.len;
	
	m->m_flags |= M_PROTO1; //set to avoid loops 
	
	error = ifnet_output_raw(dst_ifp, 0, m);
	if (error == 0) {
		(void) ifnet_stat_increment_out(dst_ifp, 1, len, 0);
	} else {
		(void) ifnet_stat_increment_out(dst_ifp, 0, 0, 1);
	}
}