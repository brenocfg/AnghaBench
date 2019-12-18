#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _usb_p {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  pbcallback ;
struct TYPE_3__ {int openstate; int fd; int vid; int pid; int acl_out; int acl_in; int hci_evt; int hci_ctrl; int /*<<< orphan*/  unregcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BUF_SIZE ; 
 int /*<<< orphan*/  CTRL_BUF_SIZE ; 
 int /*<<< orphan*/  NUM_ACL_BUFS ; 
 int /*<<< orphan*/  NUM_CTRL_BUFS ; 
 scalar_t__ USB_Initialize () ; 
 scalar_t__ __IPC_ClntInit () ; 
 scalar_t__ __getDeviceId (int,int) ; 
 int /*<<< orphan*/  __initUsbIOBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __ntd_pid ; 
 int __ntd_vid ; 
 scalar_t__ __ntd_vid_pid_specified ; 
 TYPE_1__ __usbdev ; 
 int __wait4hci ; 
 int /*<<< orphan*/  aclbufs ; 
 int /*<<< orphan*/  ctrlbufs ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 __usb_register(pbcallback cb)
{
	s32 ret = 0;

	memset(&__usbdev,0,sizeof(struct _usb_p));
	__usbdev.openstate = 5;

	ret = __IPC_ClntInit();
	if(ret<0) return ret;

	ret = USB_Initialize();
	if(ret<0) return ret;

	__usbdev.fd = -1;
	__usbdev.unregcb = cb;
	if(__ntd_vid_pid_specified) {
		__usbdev.vid = __ntd_vid;
		__usbdev.pid = __ntd_pid;
	} else {
		__usbdev.vid = 0x057E;
		__usbdev.pid = 0x0305;
	}

	ret = __getDeviceId(__usbdev.vid,__usbdev.pid);
	if(ret<0) return ret;

	__usbdev.acl_out		= 0x02;
	__usbdev.acl_in			= 0x82;
	__usbdev.hci_evt		= 0x81;
	__usbdev.hci_ctrl		= 0x00;

	__initUsbIOBuffer(&ctrlbufs,CTRL_BUF_SIZE,NUM_CTRL_BUFS);
	__initUsbIOBuffer(&aclbufs,ACL_BUF_SIZE,NUM_ACL_BUFS);

	__usbdev.openstate = 4;
	__wait4hci = 1;

	return ret;
}