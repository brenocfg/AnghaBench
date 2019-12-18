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
struct bnx2x_rx_mode_ramrod_params {TYPE_1__* rx_mode_obj; int /*<<< orphan*/  ramrod_flags; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int (* config_rx_mode ) (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ;int (* wait_comp ) (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int stub1 (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ; 
 int stub2 (struct bnx2x*,struct bnx2x_rx_mode_ramrod_params*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_config_rx_mode(struct bnx2x *bp,
			 struct bnx2x_rx_mode_ramrod_params *p)
{
	int rc;

	/* Configure the new classification in the chip */
	rc = p->rx_mode_obj->config_rx_mode(bp, p);
	if (rc < 0)
		return rc;

	/* Wait for a ramrod completion if was requested */
	if (test_bit(RAMROD_COMP_WAIT, &p->ramrod_flags)) {
		rc = p->rx_mode_obj->wait_comp(bp, p);
		if (rc)
			return rc;
	}

	return rc;
}