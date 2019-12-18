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
struct bfi_phy_stats_req_s {int /*<<< orphan*/  alen; int /*<<< orphan*/  mh; int /*<<< orphan*/  instance; } ;
struct bfa_phy_stats_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_phy_s {TYPE_1__ mb; int /*<<< orphan*/  ioc; int /*<<< orphan*/  dbuf_pa; int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_PHY ; 
 int /*<<< orphan*/  BFI_PHY_H2I_STATS_REQ ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_phy_stats_send(void *cbarg)
{
	struct bfa_phy_s *phy = cbarg;
	struct bfi_phy_stats_req_s *msg =
			(struct bfi_phy_stats_req_s *) phy->mb.msg;

	msg->instance = phy->instance;
	bfi_h2i_set(msg->mh, BFI_MC_PHY, BFI_PHY_H2I_STATS_REQ,
		bfa_ioc_portid(phy->ioc));
	bfa_alen_set(&msg->alen, sizeof(struct bfa_phy_stats_s), phy->dbuf_pa);
	bfa_ioc_mbox_queue(phy->ioc, &phy->mb);
}