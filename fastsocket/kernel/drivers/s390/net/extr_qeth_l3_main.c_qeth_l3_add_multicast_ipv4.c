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
struct qeth_card {int /*<<< orphan*/  dev; } ;
struct in_device {int /*<<< orphan*/  mc_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 struct in_device* in_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 
 int /*<<< orphan*/  qeth_l3_add_mc (struct qeth_card*,struct in_device*) ; 
 int /*<<< orphan*/  qeth_l3_add_vlan_mc (struct qeth_card*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_l3_add_multicast_ipv4(struct qeth_card *card)
{
	struct in_device *in4_dev;

	QETH_DBF_TEXT(TRACE, 4, "chkmcv4");
	in4_dev = in_dev_get(card->dev);
	if (in4_dev == NULL)
		return;
	read_lock(&in4_dev->mc_list_lock);
	qeth_l3_add_mc(card, in4_dev);
	qeth_l3_add_vlan_mc(card);
	read_unlock(&in4_dev->mc_list_lock);
	in_dev_put(in4_dev);
}