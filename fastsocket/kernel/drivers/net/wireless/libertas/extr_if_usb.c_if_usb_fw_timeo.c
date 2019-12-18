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
struct if_usb_card {int surprise_removed; int /*<<< orphan*/  fw_wq; scalar_t__ fwdnldover; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbs_deb_usb (char*) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_usb_fw_timeo(unsigned long priv)
{
	struct if_usb_card *cardp = (void *)priv;

	if (cardp->fwdnldover) {
		lbs_deb_usb("Download complete, no event. Assuming success\n");
	} else {
		lbs_pr_err("Download timed out\n");
		cardp->surprise_removed = 1;
	}
	wake_up(&cardp->fw_wq);
}