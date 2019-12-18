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
struct rtl_fw {int /*<<< orphan*/  fw; } ;
struct rtl8169_private {struct rtl_fw* rtl_fw; int /*<<< orphan*/  dev; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  kfree (struct rtl_fw*) ; 
 struct rtl_fw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int request_firmware (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int rtl_check_firmware (struct rtl8169_private*,struct rtl_fw*) ; 
 char* rtl_lookup_firmware_name (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_request_uncached_firmware(struct rtl8169_private *tp)
{
	struct rtl_fw *rtl_fw;
	const char *name;
	int rc = -ENOMEM;

	name = rtl_lookup_firmware_name(tp);
	if (!name)
		goto out_no_firmware;

	rtl_fw = kzalloc(sizeof(*rtl_fw), GFP_KERNEL);
	if (!rtl_fw)
		goto err_warn;

	rc = request_firmware(&rtl_fw->fw, name, &tp->pci_dev->dev);
	if (rc < 0)
		goto err_free;

	rc = rtl_check_firmware(tp, rtl_fw);
	if (rc < 0)
		goto err_release_firmware;

	tp->rtl_fw = rtl_fw;
out:
	return;

err_release_firmware:
	release_firmware(rtl_fw->fw);
err_free:
	kfree(rtl_fw);
err_warn:
	netif_warn(tp, ifup, tp->dev, "unable to load firmware patch %s (%d)\n",
		   name, rc);
out_no_firmware:
	tp->rtl_fw = NULL;
	goto out;
}