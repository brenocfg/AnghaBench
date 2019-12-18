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
struct iscsi_cls_session {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TRANS_SESSION (struct iscsi_cls_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_KEVENT_DESTROY_SESSION ; 
 int /*<<< orphan*/  iscsi_session_event (struct iscsi_cls_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void iscsi_free_session(struct iscsi_cls_session *session)
{
	ISCSI_DBG_TRANS_SESSION(session, "Freeing session\n");
	iscsi_session_event(session, ISCSI_KEVENT_DESTROY_SESSION);
	put_device(&session->dev);
}