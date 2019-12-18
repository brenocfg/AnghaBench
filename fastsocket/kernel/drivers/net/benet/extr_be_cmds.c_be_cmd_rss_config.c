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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct be_mcc_wrb {int dummy; } ;
struct TYPE_2__ {int version; } ;
struct be_cmd_req_rss_config {int /*<<< orphan*/  hash; int /*<<< orphan*/  cpu_table; TYPE_1__ hdr; void* cpu_table_size_log2; void* enable_rss; int /*<<< orphan*/  if_id; } ;
struct be_adapter {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  if_handle; } ;
typedef  int /*<<< orphan*/  myhash ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int /*<<< orphan*/  OPCODE_ETH_RSS_CONFIG ; 
 int /*<<< orphan*/  be_dws_cpu_to_le (int /*<<< orphan*/ ,int) ; 
 int be_mbox_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct be_cmd_req_rss_config* embedded_payload (struct be_mcc_wrb*) ; 
 int fls (int) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 
 struct be_mcc_wrb* wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_rss_config(struct be_adapter *adapter, u8 *rsstable,
			u32 rss_hash_opts, u16 table_size)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_rss_config *req;
	u32 myhash[10] = {0x15d43fa5, 0x2534685a, 0x5f87693a, 0x5668494e,
			0x33cf6a53, 0x383334c6, 0x76ac4257, 0x59b242b2,
			0x3ea83c02, 0x4a110304};
	int status;

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	wrb = wrb_from_mbox(adapter);
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
		OPCODE_ETH_RSS_CONFIG, sizeof(*req), wrb, NULL);

	req->if_id = cpu_to_le32(adapter->if_handle);
	req->enable_rss = cpu_to_le16(rss_hash_opts);
	req->cpu_table_size_log2 = cpu_to_le16(fls(table_size) - 1);

	if (lancer_chip(adapter) || skyhawk_chip(adapter))
		req->hdr.version = 1;

	memcpy(req->cpu_table, rsstable, table_size);
	memcpy(req->hash, myhash, sizeof(myhash));
	be_dws_cpu_to_le(req->hash, sizeof(req->hash));

	status = be_mbox_notify_wait(adapter);

	mutex_unlock(&adapter->mbox_lock);
	return status;
}