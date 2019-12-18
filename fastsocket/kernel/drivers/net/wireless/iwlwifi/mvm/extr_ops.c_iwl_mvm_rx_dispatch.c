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
typedef  size_t u8 ;
struct TYPE_3__ {scalar_t__ cmd; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_rx_handlers {scalar_t__ cmd_id; int (* fn ) (struct iwl_mvm*,struct iwl_rx_cmd_buffer*,struct iwl_device_cmd*) ;int /*<<< orphan*/  async; } ;
struct iwl_rx_cmd_buffer {int /*<<< orphan*/  _rx_page_order; int /*<<< orphan*/  _offset; } ;
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  async_handlers_wk; int /*<<< orphan*/  async_handlers_lock; int /*<<< orphan*/  async_handlers_list; int /*<<< orphan*/  notif_wait; } ;
struct iwl_device_cmd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  _rx_page_order; int /*<<< orphan*/  _offset; int /*<<< orphan*/  _page; } ;
struct iwl_async_handler_entry {int (* fn ) (struct iwl_mvm*,struct iwl_rx_cmd_buffer*,struct iwl_device_cmd*) ;int /*<<< orphan*/  list; TYPE_2__ rxb; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct iwl_rx_handlers*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 struct iwl_rx_handlers* iwl_mvm_rx_handlers ; 
 int /*<<< orphan*/  iwl_notification_wait_notify (int /*<<< orphan*/ *,struct iwl_rx_packet*) ; 
 struct iwl_async_handler_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  rxb_steal_page (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct iwl_mvm*,struct iwl_rx_cmd_buffer*,struct iwl_device_cmd*) ; 

__attribute__((used)) static int iwl_mvm_rx_dispatch(struct iwl_op_mode *op_mode,
			       struct iwl_rx_cmd_buffer *rxb,
			       struct iwl_device_cmd *cmd)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	u8 i;

	/*
	 * Do the notification wait before RX handlers so
	 * even if the RX handler consumes the RXB we have
	 * access to it in the notification wait entry.
	 */
	iwl_notification_wait_notify(&mvm->notif_wait, pkt);

	for (i = 0; i < ARRAY_SIZE(iwl_mvm_rx_handlers); i++) {
		const struct iwl_rx_handlers *rx_h = &iwl_mvm_rx_handlers[i];
		struct iwl_async_handler_entry *entry;

		if (rx_h->cmd_id != pkt->hdr.cmd)
			continue;

		if (!rx_h->async)
			return rx_h->fn(mvm, rxb, cmd);

		entry = kzalloc(sizeof(*entry), GFP_ATOMIC);
		/* we can't do much... */
		if (!entry)
			return 0;

		entry->rxb._page = rxb_steal_page(rxb);
		entry->rxb._offset = rxb->_offset;
		entry->rxb._rx_page_order = rxb->_rx_page_order;
		entry->fn = rx_h->fn;
		spin_lock(&mvm->async_handlers_lock);
		list_add_tail(&entry->list, &mvm->async_handlers_list);
		spin_unlock(&mvm->async_handlers_lock);
		schedule_work(&mvm->async_handlers_wk);
		break;
	}

	return 0;
}