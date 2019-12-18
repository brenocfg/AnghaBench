#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct usbtxbuf {void* rpData; int /*<<< orphan*/  txsize; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int openstate; int /*<<< orphan*/  hci_evt; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_ENOMEM ; 
 int /*<<< orphan*/  IPC_OK ; 
 int /*<<< orphan*/  ROUNDDOWN32 (scalar_t__) ; 
 scalar_t__ ROUNDUP32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_ReadIntrMsgAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct usbtxbuf*) ; 
 int /*<<< orphan*/  __readintrdataCB ; 
 TYPE_3__ __usbdev ; 
 scalar_t__ btmemb_alloc (TYPE_1__*) ; 
 TYPE_1__ ctrlbufs ; 

__attribute__((used)) static s32 __issue_intrread()
{
	s32 ret;
	u32 len;
	u8 *ptr;
	struct usbtxbuf *buf;

	if(__usbdev.openstate!=0x0002) return IPC_OK;

	buf = (struct usbtxbuf*)btmemb_alloc(&ctrlbufs);
	if(buf!=NULL) {
		ptr = (u8*)((u32)buf + sizeof(struct usbtxbuf));
		buf->rpData = (void*)ROUNDUP32(ptr);
		len = (ctrlbufs.size - ((u32)buf->rpData - (u32)buf));
		buf->txsize = ROUNDDOWN32(len);
		ret = USB_ReadIntrMsgAsync(__usbdev.fd,__usbdev.hci_evt,buf->txsize,buf->rpData,__readintrdataCB,buf);
	} else
		ret = IPC_ENOMEM;

	return ret;
}