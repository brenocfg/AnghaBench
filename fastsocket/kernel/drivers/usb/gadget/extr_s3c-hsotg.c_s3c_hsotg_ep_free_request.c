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
struct usb_ep {int dummy; } ;
struct s3c_hsotg_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct s3c_hsotg_req*) ; 
 struct s3c_hsotg_req* our_req (struct usb_request*) ; 

__attribute__((used)) static void s3c_hsotg_ep_free_request(struct usb_ep *ep,
				      struct usb_request *req)
{
	struct s3c_hsotg_req *hs_req = our_req(req);

	kfree(hs_req);
}