#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hidp_session {TYPE_2__* conn; TYPE_1__* ctrl_sock; } ;
struct hci_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_5__ {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 TYPE_3__* bt_sk (int /*<<< orphan*/ ) ; 
 TYPE_2__* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 struct hci_dev* hci_get_route (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct device *hidp_get_device(struct hidp_session *session)
{
	bdaddr_t *src = &bt_sk(session->ctrl_sock->sk)->src;
	bdaddr_t *dst = &bt_sk(session->ctrl_sock->sk)->dst;
	struct device *device = NULL;
	struct hci_dev *hdev;

	hdev = hci_get_route(dst, src);
	if (!hdev)
		return NULL;

	session->conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, dst);
	if (session->conn)
		device = &session->conn->dev;

	hci_dev_put(hdev);

	return device;
}