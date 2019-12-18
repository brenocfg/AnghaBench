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
struct msg_queue {int /*<<< orphan*/  q_perm; } ;

/* Variables and functions */
#define  IPC_INFO 133 
#define  IPC_RMID 132 
#define  IPC_SET 131 
#define  IPC_STAT 130 
 int MSGQ__ASSOCIATE ; 
 int MSGQ__DESTROY ; 
 int MSGQ__GETATTR ; 
 int MSGQ__SETATTR ; 
#define  MSG_INFO 129 
#define  MSG_STAT 128 
 int /*<<< orphan*/  SYSTEM__IPC_INFO ; 
 int /*<<< orphan*/  current ; 
 int ipc_has_perm (int /*<<< orphan*/ *,int) ; 
 int task_has_system (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_msg_queue_msgctl(struct msg_queue *msq, int cmd)
{
	int err;
	int perms;

	switch (cmd) {
	case IPC_INFO:
	case MSG_INFO:
		/* No specific object, just general system-wide information. */
		return task_has_system(current, SYSTEM__IPC_INFO);
	case IPC_STAT:
	case MSG_STAT:
		perms = MSGQ__GETATTR | MSGQ__ASSOCIATE;
		break;
	case IPC_SET:
		perms = MSGQ__SETATTR;
		break;
	case IPC_RMID:
		perms = MSGQ__DESTROY;
		break;
	default:
		return 0;
	}

	err = ipc_has_perm(&msq->q_perm, perms);
	return err;
}