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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  key; struct ipc_security_struct* security; } ;
struct msg_queue {TYPE_2__ q_perm; } ;
struct ipc_security_struct {int /*<<< orphan*/  sid; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipc_id; } ;
struct common_audit_data {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_AUDIT_DATA_INIT (struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC ; 
 int /*<<< orphan*/  MSGQ__ASSOCIATE ; 
 int /*<<< orphan*/  SECCLASS_MSGQ ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  current_sid () ; 

__attribute__((used)) static int selinux_msg_queue_associate(struct msg_queue *msq, int msqflg)
{
	struct ipc_security_struct *isec;
	struct common_audit_data ad;
	u32 sid = current_sid();

	isec = msq->q_perm.security;

	COMMON_AUDIT_DATA_INIT(&ad, IPC);
	ad.u.ipc_id = msq->q_perm.key;

	return avc_has_perm(sid, isec->sid, SECCLASS_MSGQ,
			    MSGQ__ASSOCIATE, &ad);
}