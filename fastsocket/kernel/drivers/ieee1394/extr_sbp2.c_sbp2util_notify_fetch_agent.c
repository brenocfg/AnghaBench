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
typedef  scalar_t__ u64 ;
struct sbp2_lu {int /*<<< orphan*/  shost; int /*<<< orphan*/  state; scalar_t__ command_block_agent_addr; int /*<<< orphan*/  ne; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 scalar_t__ SBP2LU_STATE_IN_RESET ; 
 int /*<<< orphan*/  SBP2_ERR (char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ hpsb_node_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sbp2util_notify_fetch_agent(struct sbp2_lu *lu, u64 offset,
					quadlet_t *data, size_t len)
{
	/* There is a small window after a bus reset within which the node
	 * entry's generation is current but the reconnect wasn't completed. */
	if (unlikely(atomic_read(&lu->state) == SBP2LU_STATE_IN_RESET))
		return;

	if (hpsb_node_write(lu->ne, lu->command_block_agent_addr + offset,
			    data, len))
		SBP2_ERR("sbp2util_notify_fetch_agent failed.");

	/* Now accept new SCSI commands, unless a bus reset happended during
	 * hpsb_node_write. */
	if (likely(atomic_read(&lu->state) != SBP2LU_STATE_IN_RESET))
		scsi_unblock_requests(lu->shost);
}