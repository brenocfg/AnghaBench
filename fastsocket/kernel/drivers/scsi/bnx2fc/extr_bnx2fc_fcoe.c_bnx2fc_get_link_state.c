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
struct bnx2fc_hba {int /*<<< orphan*/  adapter_state; TYPE_1__* phys_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_LINK_DOWN ; 
 int /*<<< orphan*/  __LINK_STATE_NOCARRIER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnx2fc_get_link_state(struct bnx2fc_hba *hba)
{
	if (test_bit(__LINK_STATE_NOCARRIER, &hba->phys_dev->state))
		set_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
	else
		clear_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
}