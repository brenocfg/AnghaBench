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
struct usbip_header {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
#define  USBIP_CMD_SUBMIT 129 
#define  USBIP_RET_SUBMIT 128 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  usbip_pack_cmd_submit (struct usbip_header*,struct urb*,int) ; 
 int /*<<< orphan*/  usbip_pack_ret_submit (struct usbip_header*,struct urb*,int) ; 

void usbip_pack_pdu(struct usbip_header *pdu, struct urb *urb, int cmd,
								int pack)
{
	switch (cmd) {
	case USBIP_CMD_SUBMIT:
		usbip_pack_cmd_submit(pdu, urb, pack);
		break;
	case USBIP_RET_SUBMIT:
		usbip_pack_ret_submit(pdu, urb, pack);
		break;
	default:
		err("unknown command");
		/* NOTREACHED */
		/* BUG(); */
	}
}