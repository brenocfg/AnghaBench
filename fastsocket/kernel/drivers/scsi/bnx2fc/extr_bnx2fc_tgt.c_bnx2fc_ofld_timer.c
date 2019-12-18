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
struct bnx2fc_rport {int /*<<< orphan*/  ofld_wait; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_FLAG_ENABLED ; 
 int /*<<< orphan*/  BNX2FC_FLAG_OFFLOADED ; 
 int /*<<< orphan*/  BNX2FC_FLAG_OFLD_REQ_CMPL ; 
 int /*<<< orphan*/  BNX2FC_TGT_DBG (struct bnx2fc_rport*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2fc_ofld_timer(unsigned long data)
{

	struct bnx2fc_rport *tgt = (struct bnx2fc_rport *)data;

	BNX2FC_TGT_DBG(tgt, "entered bnx2fc_ofld_timer\n");
	/* NOTE: This function should never be called, as
	 * offload should never timeout
	 */
	/*
	 * If the timer has expired, this session is dead
	 * Clear offloaded flag and logout of this device.
	 * Since OFFLOADED flag is cleared, this case
	 * will be considered as offload error and the
	 * port will be logged off, and conn_id, session
	 * resources are freed up in bnx2fc_offload_session
	 */
	clear_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags);
	clear_bit(BNX2FC_FLAG_ENABLED, &tgt->flags);
	set_bit(BNX2FC_FLAG_OFLD_REQ_CMPL, &tgt->flags);
	wake_up_interruptible(&tgt->ofld_wait);
}