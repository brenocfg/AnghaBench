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
struct usb_ctrlrequest {void* wLength; void* wIndex; void* wValue; void* bRequest; void* bRequestType; } ;
struct kaweth_device {int /*<<< orphan*/  dev; } ;
typedef  void* __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 scalar_t__ in_interrupt () ; 
 int kaweth_internal_control_msg (int /*<<< orphan*/ ,unsigned int,struct usb_ctrlrequest*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct usb_ctrlrequest*) ; 
 struct usb_ctrlrequest* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_control(struct kaweth_device *kaweth,
			  unsigned int pipe,
			  __u8 request,
			  __u8 requesttype,
			  __u16 value,
			  __u16 index,
			  void *data,
			  __u16 size,
			  int timeout)
{
	struct usb_ctrlrequest *dr;
	int retval;

	dbg("kaweth_control()");

	if(in_interrupt()) {
		dbg("in_interrupt()");
		return -EBUSY;
	}

	dr = kmalloc(sizeof(struct usb_ctrlrequest), GFP_ATOMIC);

	if (!dr) {
		dbg("kmalloc() failed");
		return -ENOMEM;
	}

	dr->bRequestType = requesttype;
	dr->bRequest = request;
	dr->wValue = cpu_to_le16(value);
	dr->wIndex = cpu_to_le16(index);
	dr->wLength = cpu_to_le16(size);

	retval = kaweth_internal_control_msg(kaweth->dev,
					     pipe,
					     dr,
					     data,
					     size,
					     timeout);

	kfree(dr);
	return retval;
}