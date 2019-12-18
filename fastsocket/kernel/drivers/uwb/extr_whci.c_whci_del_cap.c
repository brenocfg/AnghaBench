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
struct whci_card {struct umc_dev** devs; } ;
struct umc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  umc_device_unregister (struct umc_dev*) ; 

__attribute__((used)) static void whci_del_cap(struct whci_card *card, int n)
{
	struct umc_dev *umc = card->devs[n];

	if (umc != NULL)
		umc_device_unregister(umc);
}