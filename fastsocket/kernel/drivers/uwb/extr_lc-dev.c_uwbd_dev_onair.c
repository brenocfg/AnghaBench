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
struct device {TYPE_3__* parent; } ;
struct TYPE_5__ {struct device dev; } ;
struct uwb_rc {TYPE_2__ uwb_dev; } ;
struct uwb_dev {struct uwb_beca_e* bce; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mac_addr; } ;
struct uwb_beca_e {struct uwb_dev* uwb_dev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * mac_addr; } ;
typedef  int /*<<< orphan*/  macbuf ;
typedef  int /*<<< orphan*/  devbuf ;
struct TYPE_6__ {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UWB_ADDR_STRSIZE ; 
 int /*<<< orphan*/  UWB_NOTIF_ONAIR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct uwb_dev*) ; 
 struct uwb_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_bce_get (struct uwb_beca_e*) ; 
 int uwb_dev_add (struct uwb_dev*,struct device*,struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_dev_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_init (struct uwb_dev*) ; 
 int /*<<< orphan*/  uwb_mac_addr_print (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_notify (struct uwb_rc*,struct uwb_dev*,int /*<<< orphan*/ ) ; 

void uwbd_dev_onair(struct uwb_rc *rc, struct uwb_beca_e *bce)
{
	int result;
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_dev *uwb_dev;
	char macbuf[UWB_ADDR_STRSIZE], devbuf[UWB_ADDR_STRSIZE];

	uwb_mac_addr_print(macbuf, sizeof(macbuf), bce->mac_addr);
	uwb_dev_addr_print(devbuf, sizeof(devbuf), &bce->dev_addr);
	uwb_dev = kzalloc(sizeof(struct uwb_dev), GFP_KERNEL);
	if (uwb_dev == NULL) {
		dev_err(dev, "new device %s: Cannot allocate memory\n",
			macbuf);
		return;
	}
	uwb_dev_init(uwb_dev);		/* This sets refcnt to one, we own it */
	uwb_dev->mac_addr = *bce->mac_addr;
	uwb_dev->dev_addr = bce->dev_addr;
	dev_set_name(&uwb_dev->dev, macbuf);
	result = uwb_dev_add(uwb_dev, &rc->uwb_dev.dev, rc);
	if (result < 0) {
		dev_err(dev, "new device %s: cannot instantiate device\n",
			macbuf);
		goto error_dev_add;
	}
	/* plug the beacon cache */
	bce->uwb_dev = uwb_dev;
	uwb_dev->bce = bce;
	uwb_bce_get(bce);		/* released in uwb_dev_sys_release() */
	dev_info(dev, "uwb device (mac %s dev %s) connected to %s %s\n",
		 macbuf, devbuf, rc->uwb_dev.dev.parent->bus->name,
		 dev_name(rc->uwb_dev.dev.parent));
	uwb_notify(rc, uwb_dev, UWB_NOTIF_ONAIR);
	return;

error_dev_add:
	kfree(uwb_dev);
	return;
}