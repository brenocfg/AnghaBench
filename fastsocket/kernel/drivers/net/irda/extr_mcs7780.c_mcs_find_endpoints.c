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
struct TYPE_2__ {int bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_1__ desc; } ;
struct mcs_cb {int ep_in; int ep_out; } ;

/* Variables and functions */
 int USB_DIR_IN ; 

__attribute__((used)) static inline int mcs_find_endpoints(struct mcs_cb *mcs,
				     struct usb_host_endpoint *ep, int epnum)
{
	int i;
	int ret = 0;

	/* If no place to store the endpoints just return */
	if (!ep)
		return ret;

	/* cycle through all endpoints, find the first two that are DIR_IN */
	for (i = 0; i < epnum; i++) {
		if (ep[i].desc.bEndpointAddress & USB_DIR_IN)
			mcs->ep_in = ep[i].desc.bEndpointAddress;
		else
			mcs->ep_out = ep[i].desc.bEndpointAddress;

		/* MosChip says that the chip has only two bulk
		 * endpoints. Find one for each direction and move on.
		 */
		if ((mcs->ep_in != 0) && (mcs->ep_out != 0)) {
			ret = 1;
			break;
		}
	}

	return ret;
}