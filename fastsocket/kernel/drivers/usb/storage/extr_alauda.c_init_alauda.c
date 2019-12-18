#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_host_interface {TYPE_2__* endpoint; } ;
struct us_data {int /*<<< orphan*/  pusb_dev; int /*<<< orphan*/  extra_destructor; scalar_t__ extra; TYPE_3__* pusb_intf; } ;
struct alauda_info {int /*<<< orphan*/  wr_ep; } ;
struct TYPE_6__ {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_4__ {int bEndpointAddress; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*) ; 
 int /*<<< orphan*/  alauda_info_destructor ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_init_ecc () ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_alauda(struct us_data *us)
{
	struct alauda_info *info;
	struct usb_host_interface *altsetting = us->pusb_intf->cur_altsetting;
	nand_init_ecc();

	us->extra = kzalloc(sizeof(struct alauda_info), GFP_NOIO);
	if (!us->extra) {
		US_DEBUGP("init_alauda: Gah! Can't allocate storage for"
			"alauda info struct!\n");
		return USB_STOR_TRANSPORT_ERROR;
	}
	info = (struct alauda_info *) us->extra;
	us->extra_destructor = alauda_info_destructor;

	info->wr_ep = usb_sndbulkpipe(us->pusb_dev,
		altsetting->endpoint[0].desc.bEndpointAddress
		& USB_ENDPOINT_NUMBER_MASK);

	return USB_STOR_TRANSPORT_GOOD;
}