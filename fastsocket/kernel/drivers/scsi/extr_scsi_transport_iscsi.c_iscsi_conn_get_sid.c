#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_cls_session {int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iscsi_cls_conn {TYPE_1__ dev; } ;

/* Variables and functions */
 struct iscsi_cls_session* iscsi_dev_to_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t iscsi_conn_get_sid(struct iscsi_cls_conn *conn)
{
	struct iscsi_cls_session *sess = iscsi_dev_to_session(conn->dev.parent);
	return sess->sid;
}