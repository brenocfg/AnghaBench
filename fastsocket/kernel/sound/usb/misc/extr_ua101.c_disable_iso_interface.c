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
struct TYPE_4__ {scalar_t__ bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct ua101 {TYPE_3__* dev; int /*<<< orphan*/  states; TYPE_2__** intf; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_error_string (int) ; 
 int usb_set_interface (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_iso_interface(struct ua101 *ua, unsigned int intf_index)
{
	struct usb_host_interface *alts;

	if (!ua->intf[intf_index])
		return;

	alts = ua->intf[intf_index]->cur_altsetting;
	if (alts->desc.bAlternateSetting != 0) {
		int err = usb_set_interface(ua->dev,
					    alts->desc.bInterfaceNumber, 0);
		if (err < 0 && !test_bit(DISCONNECTED, &ua->states))
			dev_warn(&ua->dev->dev,
				 "interface reset failed; error %d: %s\n",
				 err, usb_error_string(err));
	}
}