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
struct bna_ethport {int /*<<< orphan*/  link_status; TYPE_1__* bna; int /*<<< orphan*/  (* link_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct bfi_msgq_mhdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bnad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_LINK_UP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_bfi_ethport_linkup_aen(struct bna_ethport *ethport,
			struct bfi_msgq_mhdr *msghdr)
{
	ethport->link_status = BNA_LINK_UP;

	/* Dispatch events */
	ethport->link_cbfn(ethport->bna->bnad, ethport->link_status);
}