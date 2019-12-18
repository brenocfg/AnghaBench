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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16_t ;
struct usbtxbuf {void* rpData; scalar_t__ txsize; } ;
struct pbuf {scalar_t__ len; scalar_t__ payload; struct pbuf* next; } ;
struct memb_blks {int dummy; } ;
struct TYPE_2__ {int openstate; int /*<<< orphan*/  acl_out; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ HCI_ACL_DATA_PACKET ; 
 scalar_t__ HCI_COMMAND_DATA_PACKET ; 
 scalar_t__ ROUNDUP32 (scalar_t__) ; 
 int /*<<< orphan*/  USB_WriteBlkMsgAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,struct usbtxbuf*) ; 
 int /*<<< orphan*/  USB_WriteCtrlMsgAsync (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,struct usbtxbuf*) ; 
 TYPE_1__ __usbdev ; 
 int /*<<< orphan*/  __writebulkmsgCB ; 
 int /*<<< orphan*/  __writectrlmsgCB ; 
 struct memb_blks aclbufs ; 
 struct usbtxbuf* btmemb_alloc (struct memb_blks*) ; 
 struct memb_blks ctrlbufs ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,scalar_t__) ; 

void physbusif_output(struct pbuf *p,u16_t len)
{
	u32 pos;
	u8 *ptr;
	struct pbuf *q;
	struct memb_blks *mblks;
	struct usbtxbuf *blkbuf;

	if(__usbdev.openstate!=0x0002) return;

	if(((u8*)p->payload)[0]==HCI_COMMAND_DATA_PACKET) mblks = &ctrlbufs;
	else if(((u8*)p->payload)[0]==HCI_ACL_DATA_PACKET) mblks = &aclbufs;
	else return;

	blkbuf = btmemb_alloc(mblks);
	if(blkbuf!=NULL) {
		blkbuf->txsize = --len;
		blkbuf->rpData = (void*)ROUNDUP32(((u32)blkbuf+sizeof(struct usbtxbuf)));

		ptr = blkbuf->rpData;
		for(q=p,pos=1;q!=NULL && len>0;q=q->next,pos=0) {
			memcpy(ptr,q->payload+pos,(q->len-pos));
			ptr += (q->len-pos);
			len -= (q->len-pos);
		}

		if(((u8*)p->payload)[0]==HCI_COMMAND_DATA_PACKET) {
			USB_WriteCtrlMsgAsync(__usbdev.fd,0x20,0,0,0,blkbuf->txsize,blkbuf->rpData,__writectrlmsgCB,blkbuf);
		} else if(((u8*)p->payload)[0]==HCI_ACL_DATA_PACKET) {
			USB_WriteBlkMsgAsync(__usbdev.fd,__usbdev.acl_out,blkbuf->txsize,blkbuf->rpData,__writebulkmsgCB,blkbuf);
		}
	}
}