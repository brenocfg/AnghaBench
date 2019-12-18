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
struct iscsi_cls_conn {int /*<<< orphan*/  dev; int /*<<< orphan*/  conn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TRANS_CONN (struct iscsi_cls_conn*,char*) ; 
 int /*<<< orphan*/  connlock ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transport_unregister_device (int /*<<< orphan*/ *) ; 

int iscsi_destroy_conn(struct iscsi_cls_conn *conn)
{
	unsigned long flags;

	spin_lock_irqsave(&connlock, flags);
	list_del(&conn->conn_list);
	spin_unlock_irqrestore(&connlock, flags);

	transport_unregister_device(&conn->dev);
	ISCSI_DBG_TRANS_CONN(conn, "Completing conn destruction\n");
	device_unregister(&conn->dev);
	return 0;
}