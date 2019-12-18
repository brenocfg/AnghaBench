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
struct hci_dev {int dummy; } ;
struct device {int dummy; } ;
struct hci_conn {struct device dev; } ;
struct bnep_session {TYPE_1__* sock; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 TYPE_2__* bt_sk (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 struct hci_dev* hci_get_route (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct device *bnep_get_device(struct bnep_session *session)
{
	bdaddr_t *src = &bt_sk(session->sock->sk)->src;
	bdaddr_t *dst = &bt_sk(session->sock->sk)->dst;
	struct hci_dev *hdev;
	struct hci_conn *conn;

	hdev = hci_get_route(dst, src);
	if (!hdev)
		return NULL;

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, dst);

	hci_dev_put(hdev);

	return conn ? &conn->dev : NULL;
}