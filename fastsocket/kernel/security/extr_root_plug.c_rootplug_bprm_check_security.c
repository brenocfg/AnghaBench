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
struct usb_device {int dummy; } ;
struct linux_binprm {TYPE_1__* cred; int /*<<< orphan*/  filename; } ;
struct TYPE_2__ {scalar_t__ egid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  product_id ; 
 int /*<<< orphan*/  root_dbg (char*,...) ; 
 struct usb_device* usb_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  vendor_id ; 

__attribute__((used)) static int rootplug_bprm_check_security (struct linux_binprm *bprm)
{
	struct usb_device *dev;

	root_dbg("file %s, e_uid = %d, e_gid = %d\n",
		 bprm->filename, bprm->cred->euid, bprm->cred->egid);

	if (bprm->cred->egid == 0) {
		dev = usb_find_device(vendor_id, product_id);
		if (!dev) {
			root_dbg("e_gid = 0, and device not found, "
				 "task not allowed to run...\n");
			return -EPERM;
		}
		usb_put_dev(dev);
	}

	return 0;
}