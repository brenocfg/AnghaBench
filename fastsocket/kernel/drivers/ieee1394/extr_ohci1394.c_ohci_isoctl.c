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
typedef  int /*<<< orphan*/  u64 ;
struct hpsb_iso_packet_info {int dummy; } ;
struct hpsb_iso {int dummy; } ;
typedef  enum isoctl_cmd { ____Placeholder_isoctl_cmd } isoctl_cmd ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT_G (int /*<<< orphan*/ ,char*,int) ; 
#define  RECV_FLUSH 141 
#define  RECV_INIT 140 
#define  RECV_LISTEN_CHANNEL 139 
#define  RECV_RELEASE 138 
#define  RECV_SET_CHANNEL_MASK 137 
#define  RECV_SHUTDOWN 136 
#define  RECV_START 135 
#define  RECV_STOP 134 
#define  RECV_UNLISTEN_CHANNEL 133 
#define  XMIT_INIT 132 
#define  XMIT_QUEUE 131 
#define  XMIT_SHUTDOWN 130 
#define  XMIT_START 129 
#define  XMIT_STOP 128 
 int /*<<< orphan*/  ohci_iso_recv_change_channel (struct hpsb_iso*,unsigned long,int) ; 
 int ohci_iso_recv_init (struct hpsb_iso*) ; 
 int /*<<< orphan*/  ohci_iso_recv_release (struct hpsb_iso*,struct hpsb_iso_packet_info*) ; 
 int /*<<< orphan*/  ohci_iso_recv_set_channel_mask (struct hpsb_iso*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_iso_recv_shutdown (struct hpsb_iso*) ; 
 int ohci_iso_recv_start (struct hpsb_iso*,int,int,int) ; 
 int /*<<< orphan*/  ohci_iso_recv_stop (struct hpsb_iso*) ; 
 int /*<<< orphan*/  ohci_iso_recv_task (unsigned long) ; 
 int ohci_iso_xmit_init (struct hpsb_iso*) ; 
 int ohci_iso_xmit_queue (struct hpsb_iso*,struct hpsb_iso_packet_info*) ; 
 int /*<<< orphan*/  ohci_iso_xmit_shutdown (struct hpsb_iso*) ; 
 int ohci_iso_xmit_start (struct hpsb_iso*,unsigned long) ; 
 int /*<<< orphan*/  ohci_iso_xmit_stop (struct hpsb_iso*) ; 

__attribute__((used)) static int ohci_isoctl(struct hpsb_iso *iso, enum isoctl_cmd cmd, unsigned long arg)
{

	switch(cmd) {
	case XMIT_INIT:
		return ohci_iso_xmit_init(iso);
	case XMIT_START:
		return ohci_iso_xmit_start(iso, arg);
	case XMIT_STOP:
		ohci_iso_xmit_stop(iso);
		return 0;
	case XMIT_QUEUE:
		return ohci_iso_xmit_queue(iso, (struct hpsb_iso_packet_info*) arg);
	case XMIT_SHUTDOWN:
		ohci_iso_xmit_shutdown(iso);
		return 0;

	case RECV_INIT:
		return ohci_iso_recv_init(iso);
	case RECV_START: {
		int *args = (int*) arg;
		return ohci_iso_recv_start(iso, args[0], args[1], args[2]);
	}
	case RECV_STOP:
		ohci_iso_recv_stop(iso);
		return 0;
	case RECV_RELEASE:
		ohci_iso_recv_release(iso, (struct hpsb_iso_packet_info*) arg);
		return 0;
	case RECV_FLUSH:
		ohci_iso_recv_task((unsigned long) iso);
		return 0;
	case RECV_SHUTDOWN:
		ohci_iso_recv_shutdown(iso);
		return 0;
	case RECV_LISTEN_CHANNEL:
		ohci_iso_recv_change_channel(iso, arg, 1);
		return 0;
	case RECV_UNLISTEN_CHANNEL:
		ohci_iso_recv_change_channel(iso, arg, 0);
		return 0;
	case RECV_SET_CHANNEL_MASK:
		ohci_iso_recv_set_channel_mask(iso, *((u64*) arg));
		return 0;

	default:
		PRINT_G(KERN_ERR, "ohci_isoctl cmd %d not implemented yet",
			cmd);
		break;
	}
	return -EINVAL;
}