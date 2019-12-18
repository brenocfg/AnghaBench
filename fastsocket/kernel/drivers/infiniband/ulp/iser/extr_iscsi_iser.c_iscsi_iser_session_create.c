#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iser_conn {TYPE_2__* device; } ;
struct iscsi_session {int /*<<< orphan*/  scsi_cmds_max; } ;
struct iscsi_iser_task {int dummy; } ;
struct iscsi_endpoint {struct iser_conn* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct Scsi_Host {int max_cmd_len; int /*<<< orphan*/  can_queue; scalar_t__ max_channel; scalar_t__ max_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {TYPE_1__* ib_device; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dma_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DEF_XMIT_CMDS_MAX ; 
 scalar_t__ iscsi_host_add (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* iscsi_host_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_free (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_host_remove (struct Scsi_Host*) ; 
 int /*<<< orphan*/  iscsi_iser_scsi_transport ; 
 int /*<<< orphan*/  iscsi_iser_sht ; 
 int /*<<< orphan*/  iscsi_iser_transport ; 
 int /*<<< orphan*/  iscsi_max_lun ; 
 struct iscsi_cls_session* iscsi_session_setup (int /*<<< orphan*/ *,struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iscsi_cls_session *
iscsi_iser_session_create(struct iscsi_endpoint *ep,
			  uint16_t cmds_max, uint16_t qdepth,
			  uint32_t initial_cmdsn)
{
	struct iscsi_cls_session *cls_session;
	struct iscsi_session *session;
	struct Scsi_Host *shost;
	struct iser_conn *ib_conn;

	shost = iscsi_host_alloc(&iscsi_iser_sht, 0, 0);
	if (!shost)
		return NULL;
	shost->transportt = iscsi_iser_scsi_transport;
	shost->max_lun = iscsi_max_lun;
	shost->max_id = 0;
	shost->max_channel = 0;
	shost->max_cmd_len = 16;

	/*
	 * older userspace tools (before 2.0-870) did not pass us
	 * the leading conn's ep so this will be NULL;
	 */
	if (ep)
		ib_conn = ep->dd_data;

	if (iscsi_host_add(shost,
			   ep ? ib_conn->device->ib_device->dma_device : NULL))
		goto free_host;

	/*
	 * we do not support setting can_queue cmd_per_lun from userspace yet
	 * because we preallocate so many resources
	 */
	cls_session = iscsi_session_setup(&iscsi_iser_transport, shost,
					  ISCSI_DEF_XMIT_CMDS_MAX, 0,
					  sizeof(struct iscsi_iser_task),
					  initial_cmdsn, 0);
	if (!cls_session)
		goto remove_host;
	session = cls_session->dd_data;

	shost->can_queue = session->scsi_cmds_max;
	return cls_session;

remove_host:
	iscsi_host_remove(shost);
free_host:
	iscsi_host_free(shost);
	return NULL;
}