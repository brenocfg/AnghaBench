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
struct srp_target_port {scalar_t__ state; int /*<<< orphan*/  scsi_host; int /*<<< orphan*/  cm_id; } ;

/* Variables and functions */
 scalar_t__ SRP_TARGET_REMOVED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ib_destroy_cm_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_del_scsi_host_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_disconnect_target (struct srp_target_port*) ; 
 int /*<<< orphan*/  srp_free_req_data (struct srp_target_port*) ; 
 int /*<<< orphan*/  srp_free_target_ib (struct srp_target_port*) ; 
 int /*<<< orphan*/  srp_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_remove_target(struct srp_target_port *target)
{
	WARN_ON_ONCE(target->state != SRP_TARGET_REMOVED);

	srp_del_scsi_host_attr(target->scsi_host);
	srp_remove_host(target->scsi_host);
	scsi_remove_host(target->scsi_host);
	srp_disconnect_target(target);
	ib_destroy_cm_id(target->cm_id);
	srp_free_target_ib(target);
	srp_free_req_data(target);
	scsi_host_put(target->scsi_host);
}