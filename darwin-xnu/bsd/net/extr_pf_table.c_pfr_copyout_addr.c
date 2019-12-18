#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_6__ {TYPE_2__ sin6; TYPE_1__ sin; } ;
struct pfr_kentry {scalar_t__ pfrke_af; TYPE_3__ pfrke_sa; int /*<<< orphan*/  pfrke_not; int /*<<< orphan*/  pfrke_net; } ;
struct pfr_addr {scalar_t__ pfra_af; int /*<<< orphan*/  pfra_ip6addr; int /*<<< orphan*/  pfra_ip4addr; int /*<<< orphan*/  pfra_not; int /*<<< orphan*/  pfra_net; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  bzero (struct pfr_addr*,int) ; 

__attribute__((used)) static void
pfr_copyout_addr(struct pfr_addr *ad, struct pfr_kentry *ke)
{
	bzero(ad, sizeof (*ad));
	if (ke == NULL)
		return;
	ad->pfra_af = ke->pfrke_af;
	ad->pfra_net = ke->pfrke_net;
	ad->pfra_not = ke->pfrke_not;
	if (ad->pfra_af == AF_INET)
		ad->pfra_ip4addr = ke->pfrke_sa.sin.sin_addr;
	else if (ad->pfra_af == AF_INET6)
		ad->pfra_ip6addr = ke->pfrke_sa.sin6.sin6_addr;
}