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
struct hidp_session {int /*<<< orphan*/ * rd_data; struct hid_device* hid; TYPE_1__* ctrl_sock; int /*<<< orphan*/  rd_size; } ;
struct hidp_connadd_req {int /*<<< orphan*/  name; int /*<<< orphan*/  country; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  rd_size; int /*<<< orphan*/  rd_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct hid_device {int /*<<< orphan*/  hid_output_raw_report; int /*<<< orphan*/ * ll_driver; TYPE_2__ dev; int /*<<< orphan*/  uniq; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  country; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bus; struct hidp_session* driver_data; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_BLUETOOTH ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct hid_device*) ; 
 int PTR_ERR (struct hid_device*) ; 
 int /*<<< orphan*/  baswap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 TYPE_3__* bt_sk (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hid_add_device (struct hid_device*) ; 
 struct hid_device* hid_allocate_device () ; 
 int /*<<< orphan*/  hid_destroy_device (struct hid_device*) ; 
 int /*<<< orphan*/  hidp_get_device (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_hid_driver ; 
 int /*<<< orphan*/  hidp_output_raw_report ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hidp_setup_hid(struct hidp_session *session,
				struct hidp_connadd_req *req)
{
	struct hid_device *hid;
	bdaddr_t src, dst;
	int err;

	session->rd_data = kzalloc(req->rd_size, GFP_KERNEL);
	if (!session->rd_data)
		return -ENOMEM;

	if (copy_from_user(session->rd_data, req->rd_data, req->rd_size)) {
		err = -EFAULT;
		goto fault;
	}
	session->rd_size = req->rd_size;

	hid = hid_allocate_device();
	if (IS_ERR(hid)) {
		err = PTR_ERR(hid);
		goto fault;
	}

	session->hid = hid;

	hid->driver_data = session;

	baswap(&src, &bt_sk(session->ctrl_sock->sk)->src);
	baswap(&dst, &bt_sk(session->ctrl_sock->sk)->dst);

	hid->bus     = BUS_BLUETOOTH;
	hid->vendor  = req->vendor;
	hid->product = req->product;
	hid->version = req->version;
	hid->country = req->country;

	strncpy(hid->name, req->name, sizeof(req->name) - 1);
	strncpy(hid->phys, batostr(&src), 64);
	strncpy(hid->uniq, batostr(&dst), 64);

	hid->dev.parent = hidp_get_device(session);
	hid->ll_driver = &hidp_hid_driver;

	hid->hid_output_raw_report = hidp_output_raw_report;

	err = hid_add_device(hid);
	if (err < 0)
		goto failed;

	return 0;

failed:
	hid_destroy_device(hid);
	session->hid = NULL;

fault:
	kfree(session->rd_data);
	session->rd_data = NULL;

	return err;
}