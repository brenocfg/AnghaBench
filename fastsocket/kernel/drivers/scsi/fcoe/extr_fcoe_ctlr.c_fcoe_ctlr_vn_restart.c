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
typedef  int u32 ;
struct fcoe_ctlr {int port_id; scalar_t__ probe_tries; int /*<<< orphan*/  timer; TYPE_1__* lp; int /*<<< orphan*/  rnd_state; } ;
struct TYPE_2__ {int wwpn; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIP_ST_VNMP_START ; 
 unsigned long FIP_VN_PROBE_WAIT ; 
 scalar_t__ FIP_VN_RLIM_COUNT ; 
 unsigned long FIP_VN_RLIM_INT ; 
 int /*<<< orphan*/  fcoe_ctlr_disc_stop_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  fcoe_ctlr_set_state (struct fcoe_ctlr*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 
 int prandom32 (int /*<<< orphan*/ *) ; 
 unsigned long random32 () ; 

__attribute__((used)) static void fcoe_ctlr_vn_restart(struct fcoe_ctlr *fip)
{
	unsigned long wait;
	u32 port_id;

	fcoe_ctlr_disc_stop_locked(fip->lp);

	/*
	 * Get proposed port ID.
	 * If this is the first try after link up, use any previous port_id.
	 * If there was none, use the low bits of the port_name.
	 * On subsequent tries, get the next random one.
	 * Don't use reserved IDs, use another non-zero value, just as random.
	 */
	port_id = fip->port_id;
	if (fip->probe_tries)
		port_id = prandom32(&fip->rnd_state) & 0xffff;
	else if (!port_id)
		port_id = fip->lp->wwpn & 0xffff;
	if (!port_id || port_id == 0xffff)
		port_id = 1;
	fip->port_id = port_id;

	if (fip->probe_tries < FIP_VN_RLIM_COUNT) {
		fip->probe_tries++;
		wait = random32() % FIP_VN_PROBE_WAIT;
	} else
		wait = FIP_VN_RLIM_INT;
	mod_timer(&fip->timer, jiffies + msecs_to_jiffies(wait));
	fcoe_ctlr_set_state(fip, FIP_ST_VNMP_START);
}