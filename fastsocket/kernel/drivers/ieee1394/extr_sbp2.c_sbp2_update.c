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
struct unit_directory {int /*<<< orphan*/  device; } ;
struct sbp2_lu {int /*<<< orphan*/  shost; int /*<<< orphan*/  state; int /*<<< orphan*/  ne; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int EBUSY ; 
 int /*<<< orphan*/  SBP2LU_STATE_RUNNING ; 
 int /*<<< orphan*/  SBP2_ERR (char*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sbp2_lu* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ hpsb_node_entry_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp2_agent_reset (struct sbp2_lu*,int) ; 
 scalar_t__ sbp2_login_device (struct sbp2_lu*) ; 
 int /*<<< orphan*/  sbp2_logout_device (struct sbp2_lu*) ; 
 int /*<<< orphan*/  sbp2_max_speed_and_size (struct sbp2_lu*) ; 
 scalar_t__ sbp2_reconnect_device (struct sbp2_lu*) ; 
 int /*<<< orphan*/  sbp2_set_busy_timeout (struct sbp2_lu*) ; 
 int /*<<< orphan*/  sbp2scsi_complete_all_commands (struct sbp2_lu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbp2_update(struct unit_directory *ud)
{
	struct sbp2_lu *lu = dev_get_drvdata(&ud->device);

	if (sbp2_reconnect_device(lu) != 0) {
		/*
		 * Reconnect failed.  If another bus reset happened,
		 * let nodemgr proceed and call sbp2_update again later
		 * (or sbp2_remove if this node went away).
		 */
		if (!hpsb_node_entry_valid(lu->ne))
			return 0;
		/*
		 * Or the target rejected the reconnect because we weren't
		 * fast enough.  Try a regular login, but first log out
		 * just in case of any weirdness.
		 */
		sbp2_logout_device(lu);

		if (sbp2_login_device(lu) != 0) {
			if (!hpsb_node_entry_valid(lu->ne))
				return 0;

			/* Maybe another initiator won the login. */
			SBP2_ERR("Failed to reconnect to sbp2 device!");
			return -EBUSY;
		}
	}

	sbp2_set_busy_timeout(lu);
	sbp2_agent_reset(lu, 1);
	sbp2_max_speed_and_size(lu);

	/* Complete any pending commands with busy (so they get retried)
	 * and remove them from our queue. */
	sbp2scsi_complete_all_commands(lu, DID_BUS_BUSY);

	/* Accept new commands unless there was another bus reset in the
	 * meantime. */
	if (hpsb_node_entry_valid(lu->ne)) {
		atomic_set(&lu->state, SBP2LU_STATE_RUNNING);
		scsi_unblock_requests(lu->shost);
	}
	return 0;
}