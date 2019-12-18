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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct iwl_test {int /*<<< orphan*/  trans; } ;
struct iwl_rx_packet {int /*<<< orphan*/  hdr; int /*<<< orphan*/  len_n_flags; } ;
struct iwl_host_cmd {int flags; struct iwl_rx_packet* resp_pkt; int /*<<< orphan*/ * len; int /*<<< orphan*/  id; int /*<<< orphan*/ * dataflags; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CMD_ON_DEMAND ; 
 int CMD_SYNC ; 
 int CMD_WANT_SKB ; 
 int ENOMEM ; 
 int ENOMSG ; 
 int FH_RSCSR_FRAME_SIZE_MSK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_HCMD_DFL_NOCOPY ; 
 int /*<<< orphan*/  IWL_TM_ATTR_COMMAND ; 
 size_t IWL_TM_ATTR_UCODE_CMD_DATA ; 
 size_t IWL_TM_ATTR_UCODE_CMD_ID ; 
 size_t IWL_TM_ATTR_UCODE_CMD_SKB ; 
 int /*<<< orphan*/  IWL_TM_ATTR_UCODE_RX_PKT ; 
 int /*<<< orphan*/  IWL_TM_CMD_DEV2APP_UCODE_RX_PKT ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 struct sk_buff* iwl_test_alloc_reply (struct iwl_test*,int) ; 
 int iwl_test_reply (struct iwl_test*,struct sk_buff*) ; 
 int iwl_test_send_cmd (struct iwl_test*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_host_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_get_flag (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_test_fw_cmd(struct iwl_test *tst, struct nlattr **tb)
{
	struct iwl_host_cmd cmd;
	struct iwl_rx_packet *pkt;
	struct sk_buff *skb;
	void *reply_buf;
	u32 reply_len;
	int ret;
	bool cmd_want_skb;

	memset(&cmd, 0, sizeof(struct iwl_host_cmd));

	if (!tb[IWL_TM_ATTR_UCODE_CMD_ID] ||
	    !tb[IWL_TM_ATTR_UCODE_CMD_DATA]) {
		IWL_ERR(tst->trans, "Missing fw command mandatory fields\n");
		return -ENOMSG;
	}

	cmd.flags = CMD_ON_DEMAND | CMD_SYNC;
	cmd_want_skb = nla_get_flag(tb[IWL_TM_ATTR_UCODE_CMD_SKB]);
	if (cmd_want_skb)
		cmd.flags |= CMD_WANT_SKB;

	cmd.id = nla_get_u8(tb[IWL_TM_ATTR_UCODE_CMD_ID]);
	cmd.data[0] = nla_data(tb[IWL_TM_ATTR_UCODE_CMD_DATA]);
	cmd.len[0] = nla_len(tb[IWL_TM_ATTR_UCODE_CMD_DATA]);
	cmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;
	IWL_DEBUG_INFO(tst->trans, "test fw cmd=0x%x, flags 0x%x, len %d\n",
		       cmd.id, cmd.flags, cmd.len[0]);

	ret = iwl_test_send_cmd(tst, &cmd);
	if (ret) {
		IWL_ERR(tst->trans, "Failed to send hcmd\n");
		return ret;
	}
	if (!cmd_want_skb)
		return ret;

	/* Handling return of SKB to the user */
	pkt = cmd.resp_pkt;
	if (!pkt) {
		IWL_ERR(tst->trans, "HCMD received a null response packet\n");
		return ret;
	}

	reply_len = le32_to_cpu(pkt->len_n_flags) & FH_RSCSR_FRAME_SIZE_MSK;
	skb = iwl_test_alloc_reply(tst, reply_len + 20);
	reply_buf = kmemdup(&pkt->hdr, reply_len, GFP_KERNEL);
	if (!skb || !reply_buf) {
		kfree_skb(skb);
		kfree(reply_buf);
		return -ENOMEM;
	}

	/* The reply is in a page, that we cannot send to user space. */
	iwl_free_resp(&cmd);

	if (nla_put_u32(skb, IWL_TM_ATTR_COMMAND,
			IWL_TM_CMD_DEV2APP_UCODE_RX_PKT) ||
	    nla_put(skb, IWL_TM_ATTR_UCODE_RX_PKT, reply_len, reply_buf))
		goto nla_put_failure;
	return iwl_test_reply(tst, skb);

nla_put_failure:
	IWL_DEBUG_INFO(tst->trans, "Failed creating NL attributes\n");
	kfree(reply_buf);
	kfree_skb(skb);
	return -ENOMSG;
}