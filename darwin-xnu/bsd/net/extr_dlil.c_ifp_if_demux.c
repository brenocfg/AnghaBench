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
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EJUSTRETURN ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static errno_t
ifp_if_demux(struct ifnet *ifp, struct mbuf *m, char *fh, protocol_family_t *pf)
{
#pragma unused(ifp, fh, pf)
	m_freem(m);
	return (EJUSTRETURN);
}