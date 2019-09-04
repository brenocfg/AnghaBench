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
struct TYPE_2__ {int /*<<< orphan*/  sin6; int /*<<< orphan*/  sin; } ;
struct pfr_kentry {scalar_t__ pfrke_af; int pfrke_intrpool; int /*<<< orphan*/  pfrke_not; int /*<<< orphan*/  pfrke_net; TYPE_1__ pfrke_sa; } ;
struct pfr_addr {scalar_t__ pfra_af; int /*<<< orphan*/  pfra_not; int /*<<< orphan*/  pfra_net; int /*<<< orphan*/  pfra_ip6addr; int /*<<< orphan*/  pfra_ip4addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  FILLIN_SIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILLIN_SIN6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PR_WAITOK ; 
 int /*<<< orphan*/  bzero (struct pfr_kentry*,int) ; 
 int /*<<< orphan*/  pfr_kentry_pl ; 
 int /*<<< orphan*/  pfr_kentry_pl2 ; 
 struct pfr_kentry* pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pfr_kentry *
pfr_create_kentry(struct pfr_addr *ad, int intr)
{
	struct pfr_kentry	*ke;

	if (intr)
		ke = pool_get(&pfr_kentry_pl2, PR_WAITOK);
	else
		ke = pool_get(&pfr_kentry_pl, PR_WAITOK);
	if (ke == NULL)
		return (NULL);
	bzero(ke, sizeof (*ke));

	if (ad->pfra_af == AF_INET)
		FILLIN_SIN(ke->pfrke_sa.sin, ad->pfra_ip4addr);
	else if (ad->pfra_af == AF_INET6)
		FILLIN_SIN6(ke->pfrke_sa.sin6, ad->pfra_ip6addr);
	ke->pfrke_af = ad->pfra_af;
	ke->pfrke_net = ad->pfra_net;
	ke->pfrke_not = ad->pfra_not;
	ke->pfrke_intrpool = intr;
	return (ke);
}