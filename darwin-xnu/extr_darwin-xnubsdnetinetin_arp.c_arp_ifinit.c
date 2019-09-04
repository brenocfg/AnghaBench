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
struct sockaddr {int dummy; } ;
struct ifnet {int dummy; } ;
struct ifaddr {struct sockaddr* ifa_addr; int /*<<< orphan*/  ifa_flags; int /*<<< orphan*/  ifa_rtrequest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  IFA_LOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  RTF_CLONING ; 
 int /*<<< orphan*/  arp_rtrequest ; 
 int /*<<< orphan*/  dlil_send_arp (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 

void
arp_ifinit(struct ifnet *ifp, struct ifaddr *ifa)
{
	struct sockaddr *sa;

	IFA_LOCK(ifa);
	ifa->ifa_rtrequest = arp_rtrequest;
	ifa->ifa_flags |= RTF_CLONING;
	sa = ifa->ifa_addr;
	IFA_UNLOCK(ifa);
	dlil_send_arp(ifp, ARPOP_REQUEST, NULL, sa, NULL, sa, 0);
}