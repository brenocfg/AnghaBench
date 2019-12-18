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
typedef  int /*<<< orphan*/  u16 ;
struct be_mcc_wrb {int /*<<< orphan*/  tag1; int /*<<< orphan*/  tag0; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  head; } ;
struct be_mcc_obj {TYPE_1__ q; } ;
struct be_cmd_resp_hdr {int status; } ;
struct be_adapter {struct be_mcc_obj mcc_obj; } ;

/* Variables and functions */
 int EIO ; 
 struct be_cmd_resp_hdr* be_decode_resp_hdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_mcc_notify (struct be_adapter*) ; 
 int be_mcc_wait_compl (struct be_adapter*) ; 
 int /*<<< orphan*/  index_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* queue_index_node (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_mcc_notify_wait(struct be_adapter *adapter)
{
	int status;
	struct be_mcc_wrb *wrb;
	struct be_mcc_obj *mcc_obj = &adapter->mcc_obj;
	u16 index = mcc_obj->q.head;
	struct be_cmd_resp_hdr *resp;

	index_dec(&index, mcc_obj->q.len);
	wrb = queue_index_node(&mcc_obj->q, index);

	resp = be_decode_resp_hdr(wrb->tag0, wrb->tag1);

	be_mcc_notify(adapter);

	status = be_mcc_wait_compl(adapter);
	if (status == -EIO)
		goto out;

	status = resp->status;
out:
	return status;
}