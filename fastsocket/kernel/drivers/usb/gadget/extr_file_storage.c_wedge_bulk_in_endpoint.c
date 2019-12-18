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
struct fsg_dev {int /*<<< orphan*/  bulk_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  VDBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  WARNING (struct fsg_dev*,char*,int) ; 
 scalar_t__ msleep_interruptible (int) ; 
 int usb_ep_set_wedge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wedge_bulk_in_endpoint(struct fsg_dev *fsg)
{
	int	rc;

	DBG(fsg, "bulk-in set wedge\n");
	rc = usb_ep_set_wedge(fsg->bulk_in);
	if (rc == -EAGAIN)
		VDBG(fsg, "delayed bulk-in endpoint wedge\n");
	while (rc != 0) {
		if (rc != -EAGAIN) {
			WARNING(fsg, "usb_ep_set_wedge -> %d\n", rc);
			rc = 0;
			break;
		}

		/* Wait for a short time and then try again */
		if (msleep_interruptible(100) != 0)
			return -EINTR;
		rc = usb_ep_set_wedge(fsg->bulk_in);
	}
	return rc;
}