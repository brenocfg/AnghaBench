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
typedef  int u8_t ;
struct pbuf {scalar_t__ payload; } ;
struct TYPE_2__ {scalar_t__ num_cmd; } ;

/* Variables and functions */
 int HCI_CMD_HDR_LEN ; 
 int HCI_COMMAND_DATA_PACKET ; 
 TYPE_1__* hci_dev ; 

struct pbuf* hci_cmd_ass(struct pbuf *p,u8_t ocf,u8_t ogf,u8_t len)
{
	((u8_t*)p->payload)[0] = HCI_COMMAND_DATA_PACKET; /* cmd packet type */
	((u8_t*)p->payload)[1] = (ocf&0xff); /* OCF & OGF */
	((u8_t*)p->payload)[2] = ((ocf>>8)|(ogf<<2));
	((u8_t*)p->payload)[3] = len-HCI_CMD_HDR_LEN-1; /* Param len = plen - cmd hdr - ptype */

	if(hci_dev->num_cmd>0) hci_dev->num_cmd--;
	return p;
}