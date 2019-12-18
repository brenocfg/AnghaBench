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
typedef  int /*<<< orphan*/  u8 ;
typedef  int s32 ;
struct TYPE_2__ {int fd; int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_REQTYPE_INTERFACE_SET ; 
 int /*<<< orphan*/  USB_REQ_SETPROTOCOL ; 
 int USB_WriteCtrlMsg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* _kbd ; 

__attribute__((used)) static s32 _set_protocol(u8 protocol)
{
	if(!_kbd || _kbd->fd==-1) return -1;
	return USB_WriteCtrlMsg(_kbd->fd, USB_REQTYPE_INTERFACE_SET, USB_REQ_SETPROTOCOL, protocol, _kbd->interface, 0, NULL);
}