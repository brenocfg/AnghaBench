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
struct usb_request {int dummy; } ;
struct usb_ep {scalar_t__ name; } ;
struct dummy_request {int /*<<< orphan*/  queue; } ;
struct dummy_ep {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ ep0name ; 
 int /*<<< orphan*/  kfree (struct dummy_request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct dummy_ep* usb_ep_to_dummy_ep (struct usb_ep*) ; 
 struct dummy_request* usb_request_to_dummy_request (struct usb_request*) ; 

__attribute__((used)) static void
dummy_free_request (struct usb_ep *_ep, struct usb_request *_req)
{
	struct dummy_ep		*ep;
	struct dummy_request	*req;

	ep = usb_ep_to_dummy_ep (_ep);
	if (!ep || !_req || (!ep->desc && _ep->name != ep0name))
		return;

	req = usb_request_to_dummy_request (_req);
	WARN_ON (!list_empty (&req->queue));
	kfree (req);
}