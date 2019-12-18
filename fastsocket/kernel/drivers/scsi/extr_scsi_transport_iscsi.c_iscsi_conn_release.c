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
struct TYPE_2__ {struct device* parent; } ;
struct iscsi_cls_conn {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_TRANS_CONN (struct iscsi_cls_conn*,char*) ; 
 struct iscsi_cls_conn* iscsi_dev_to_conn (struct device*) ; 
 int /*<<< orphan*/  kfree (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void iscsi_conn_release(struct device *dev)
{
	struct iscsi_cls_conn *conn = iscsi_dev_to_conn(dev);
	struct device *parent = conn->dev.parent;

	ISCSI_DBG_TRANS_CONN(conn, "Releasing conn\n");
	kfree(conn);
	put_device(parent);
}