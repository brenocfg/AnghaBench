#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* mcl_level; } ;
struct TYPE_4__ {scalar_t__ layer2; } ;
struct qeth_card {TYPE_1__ info; TYPE_2__ options; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* CARD_DDEV_ID (struct qeth_card*) ; 
 char* CARD_RDEV_ID (struct qeth_card*) ; 
 char* CARD_WDEV_ID (struct qeth_card*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void qeth_core_get_drvinfo(struct net_device *dev,
		struct ethtool_drvinfo *info)
{
	struct qeth_card *card = dev->ml_priv;
	if (card->options.layer2)
		strcpy(info->driver, "qeth_l2");
	else
		strcpy(info->driver, "qeth_l3");

	strcpy(info->version, "1.0");
	strcpy(info->fw_version, card->info.mcl_level);
	sprintf(info->bus_info, "%s/%s/%s",
			CARD_RDEV_ID(card),
			CARD_WDEV_ID(card),
			CARD_DDEV_ID(card));
}