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
struct iscsi_cls_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TRANS_SESSION (struct iscsi_cls_session*,char*) ; 
 int /*<<< orphan*/  iscsi_free_session (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  iscsi_remove_session (struct iscsi_cls_session*) ; 

int iscsi_destroy_session(struct iscsi_cls_session *session)
{
	iscsi_remove_session(session);
	ISCSI_DBG_TRANS_SESSION(session, "Completing session destruction\n");
	iscsi_free_session(session);
	return 0;
}