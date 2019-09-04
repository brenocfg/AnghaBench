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
struct ifnet {int dummy; } ;
struct ifmediareq {int ifm_status; scalar_t__ ifm_count; } ;
typedef  int /*<<< orphan*/  ifmr ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  bzero (struct ifmediareq*,int) ; 
 scalar_t__ ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifmediareq*) ; 

__attribute__((used)) static int
interface_media_active(struct ifnet *ifp)
{
	struct ifmediareq   ifmr;
	int status = 0;

	bzero(&ifmr, sizeof(ifmr));
	if (ifnet_ioctl(ifp, 0, SIOCGIFMEDIA, &ifmr) == 0) {
		if ((ifmr.ifm_status & IFM_AVALID) && ifmr.ifm_count > 0)
			status = ifmr.ifm_status & IFM_ACTIVE ? 1 : 0;
	}

	return (status);
}