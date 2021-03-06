#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct hci_sco_hdr {int dlen; } ;
struct hci_event_hdr {scalar_t__ plen; } ;
struct hci_acl_hdr {int /*<<< orphan*/  dlen; } ;
struct TYPE_21__ {int rx_state; scalar_t__ rx_count; TYPE_6__* rx_skb; TYPE_4__* hdev; TYPE_2__* p_dev; } ;
typedef  TYPE_5__ btuart_info_t ;
struct TYPE_22__ {void* dev; } ;
struct TYPE_19__ {int /*<<< orphan*/  err_rx; int /*<<< orphan*/  byte_rx; } ;
struct TYPE_20__ {int /*<<< orphan*/  flags; TYPE_3__ stat; } ;
struct TYPE_17__ {unsigned int BasePort1; } ;
struct TYPE_18__ {TYPE_1__ io; } ;
struct TYPE_16__ {int pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_ACLDATA_PKT 134 
 scalar_t__ HCI_ACL_HDR_SIZE ; 
 scalar_t__ HCI_EVENT_HDR_SIZE ; 
#define  HCI_EVENT_PKT 133 
 int /*<<< orphan*/  HCI_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
#define  HCI_SCODATA_PKT 132 
 scalar_t__ HCI_SCO_HDR_SIZE ; 
#define  RECV_WAIT_ACL_HEADER 131 
#define  RECV_WAIT_DATA 130 
#define  RECV_WAIT_EVENT_HEADER 129 
 int RECV_WAIT_PACKET_TYPE ; 
#define  RECV_WAIT_SCO_HEADER 128 
 scalar_t__ UART_LSR ; 
 int UART_LSR_DR ; 
 scalar_t__ UART_RX ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_14__* bt_cb (TYPE_6__*) ; 
 TYPE_6__* bt_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_acl_hdr* hci_acl_hdr (TYPE_6__*) ; 
 struct hci_event_hdr* hci_event_hdr (TYPE_6__*) ; 
 int /*<<< orphan*/  hci_recv_frame (TYPE_6__*) ; 
 struct hci_sco_hdr* hci_sco_hdr (TYPE_6__*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (TYPE_6__*) ; 
 int* skb_put (TYPE_6__*,int) ; 

__attribute__((used)) static void btuart_receive(btuart_info_t *info)
{
	unsigned int iobase;
	int boguscount = 0;

	if (!info) {
		BT_ERR("Unknown device");
		return;
	}

	iobase = info->p_dev->io.BasePort1;

	do {
		info->hdev->stat.byte_rx++;

		/* Allocate packet */
		if (info->rx_skb == NULL) {
			info->rx_state = RECV_WAIT_PACKET_TYPE;
			info->rx_count = 0;
			if (!(info->rx_skb = bt_skb_alloc(HCI_MAX_FRAME_SIZE, GFP_ATOMIC))) {
				BT_ERR("Can't allocate mem for new packet");
				return;
			}
		}

		if (info->rx_state == RECV_WAIT_PACKET_TYPE) {

			info->rx_skb->dev = (void *) info->hdev;
			bt_cb(info->rx_skb)->pkt_type = inb(iobase + UART_RX);

			switch (bt_cb(info->rx_skb)->pkt_type) {

			case HCI_EVENT_PKT:
				info->rx_state = RECV_WAIT_EVENT_HEADER;
				info->rx_count = HCI_EVENT_HDR_SIZE;
				break;

			case HCI_ACLDATA_PKT:
				info->rx_state = RECV_WAIT_ACL_HEADER;
				info->rx_count = HCI_ACL_HDR_SIZE;
				break;

			case HCI_SCODATA_PKT:
				info->rx_state = RECV_WAIT_SCO_HEADER;
				info->rx_count = HCI_SCO_HDR_SIZE;
				break;

			default:
				/* Unknown packet */
				BT_ERR("Unknown HCI packet with type 0x%02x received", bt_cb(info->rx_skb)->pkt_type);
				info->hdev->stat.err_rx++;
				clear_bit(HCI_RUNNING, &(info->hdev->flags));

				kfree_skb(info->rx_skb);
				info->rx_skb = NULL;
				break;

			}

		} else {

			*skb_put(info->rx_skb, 1) = inb(iobase + UART_RX);
			info->rx_count--;

			if (info->rx_count == 0) {

				int dlen;
				struct hci_event_hdr *eh;
				struct hci_acl_hdr *ah;
				struct hci_sco_hdr *sh;


				switch (info->rx_state) {

				case RECV_WAIT_EVENT_HEADER:
					eh = hci_event_hdr(info->rx_skb);
					info->rx_state = RECV_WAIT_DATA;
					info->rx_count = eh->plen;
					break;

				case RECV_WAIT_ACL_HEADER:
					ah = hci_acl_hdr(info->rx_skb);
					dlen = __le16_to_cpu(ah->dlen);
					info->rx_state = RECV_WAIT_DATA;
					info->rx_count = dlen;
					break;

				case RECV_WAIT_SCO_HEADER:
					sh = hci_sco_hdr(info->rx_skb);
					info->rx_state = RECV_WAIT_DATA;
					info->rx_count = sh->dlen;
					break;

				case RECV_WAIT_DATA:
					hci_recv_frame(info->rx_skb);
					info->rx_skb = NULL;
					break;

				}

			}

		}

		/* Make sure we don't stay here too long */
		if (boguscount++ > 16)
			break;

	} while (inb(iobase + UART_LSR) & UART_LSR_DR);
}