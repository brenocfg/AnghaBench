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
struct sk_buff {int dummy; } ;
struct iwl_test {int /*<<< orphan*/  trans; } ;
struct iwl_rx_packet {int /*<<< orphan*/  len_n_flags; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int FH_RSCSR_FRAME_SIZE_MSK ; 
 int /*<<< orphan*/  IWL_ERR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_TM_ATTR_COMMAND ; 
 int /*<<< orphan*/  IWL_TM_ATTR_UCODE_RX_PKT ; 
 int /*<<< orphan*/  IWL_TM_CMD_DEV2APP_UCODE_RX_PKT ; 
 struct sk_buff* iwl_test_alloc_event (struct iwl_test*,int) ; 
 int /*<<< orphan*/  iwl_test_event (struct iwl_test*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct iwl_rx_packet*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static void iwl_test_send_rx(struct iwl_test *tst,
			     struct iwl_rx_cmd_buffer *rxb)
{
	struct sk_buff *skb;
	struct iwl_rx_packet *data;
	int length;

	data = rxb_addr(rxb);
	length = le32_to_cpu(data->len_n_flags) & FH_RSCSR_FRAME_SIZE_MSK;

	/* the length doesn't include len_n_flags field, so add it manually */
	length += sizeof(__le32);

	skb = iwl_test_alloc_event(tst, length + 20);
	if (skb == NULL) {
		IWL_ERR(tst->trans, "Out of memory for message to user\n");
		return;
	}

	if (nla_put_u32(skb, IWL_TM_ATTR_COMMAND,
			IWL_TM_CMD_DEV2APP_UCODE_RX_PKT) ||
	    nla_put(skb, IWL_TM_ATTR_UCODE_RX_PKT, length, data))
		goto nla_put_failure;

	iwl_test_event(tst, skb);
	return;

nla_put_failure:
	kfree_skb(skb);
	IWL_ERR(tst->trans, "Ouch, overran buffer, check allocation!\n");
}