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
struct TYPE_2__ {int /*<<< orphan*/  mtu_comp; int /*<<< orphan*/  mtu_comp_status; } ;
struct bnad {TYPE_1__ bnad_completions; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_CB_SUCCESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_cb_enet_mtu_set(struct bnad *bnad)
{
	bnad->bnad_completions.mtu_comp_status = BNA_CB_SUCCESS;
	complete(&bnad->bnad_completions.mtu_comp);
}