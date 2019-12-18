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
struct scsi_target {int /*<<< orphan*/  can_queue; } ;
struct iscsi_session {int /*<<< orphan*/  scsi_cmds_max; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;

/* Variables and functions */
 struct iscsi_cls_session* starget_to_session (struct scsi_target*) ; 

int iscsi_target_alloc(struct scsi_target *starget)
{
	struct iscsi_cls_session *cls_session = starget_to_session(starget);
	struct iscsi_session *session = cls_session->dd_data;

	starget->can_queue = session->scsi_cmds_max;
	return 0;
}