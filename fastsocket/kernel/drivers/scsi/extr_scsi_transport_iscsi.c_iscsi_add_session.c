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
struct iscsi_cls_session {unsigned int target_id; int /*<<< orphan*/  sess_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  sid; } ;
struct iscsi_cls_host {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  ISCSI_DBG_TRANS_SESSION (struct iscsi_cls_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_KEVENT_CREATE_SESSION ; 
 unsigned int ISCSI_MAX_TARGET ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int device_for_each_child (int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_cls_session_printk (int /*<<< orphan*/ ,struct iscsi_cls_session*,char*,...) ; 
 int /*<<< orphan*/  iscsi_get_next_target_id ; 
 int /*<<< orphan*/  iscsi_session_event (struct iscsi_cls_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_session_nr ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sesslist ; 
 int /*<<< orphan*/  sesslock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transport_register_device (int /*<<< orphan*/ *) ; 

int iscsi_add_session(struct iscsi_cls_session *session, unsigned int target_id)
{
	struct Scsi_Host *shost = iscsi_session_to_shost(session);
	struct iscsi_cls_host *ihost;
	unsigned long flags;
	unsigned int id = target_id;
	int err;

	ihost = shost->shost_data;
	session->sid = atomic_add_return(1, &iscsi_session_nr);

	if (id == ISCSI_MAX_TARGET) {
		for (id = 0; id < ISCSI_MAX_TARGET; id++) {
			err = device_for_each_child(&shost->shost_gendev, &id,
						    iscsi_get_next_target_id);
			if (!err)
				break;
		}

		if (id == ISCSI_MAX_TARGET) {
			iscsi_cls_session_printk(KERN_ERR, session,
						 "Too many iscsi targets. Max "
						 "number of targets is %d.\n",
						 ISCSI_MAX_TARGET - 1);
			err = -EOVERFLOW;
			goto release_host;
		}
	}
	session->target_id = id;

	dev_set_name(&session->dev, "session%u", session->sid);
	err = device_add(&session->dev);
	if (err) {
		iscsi_cls_session_printk(KERN_ERR, session,
					 "could not register session's dev\n");
		goto release_host;
	}
	transport_register_device(&session->dev);

	spin_lock_irqsave(&sesslock, flags);
	list_add(&session->sess_list, &sesslist);
	spin_unlock_irqrestore(&sesslock, flags);

	iscsi_session_event(session, ISCSI_KEVENT_CREATE_SESSION);
	ISCSI_DBG_TRANS_SESSION(session, "Completed session adding\n");
	return 0;

release_host:
	scsi_host_put(shost);
	return err;
}