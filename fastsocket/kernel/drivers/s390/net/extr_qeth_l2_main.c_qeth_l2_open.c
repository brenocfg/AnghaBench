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
struct qeth_card {int dummy; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  TRACE ; 
 int __qeth_l2_open (struct net_device*) ; 
 scalar_t__ qeth_wait_for_threads (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_open(struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;

	QETH_DBF_TEXT(TRACE, 5, "qethope_");
	if (qeth_wait_for_threads(card, QETH_RECOVER_THREAD)) {
		QETH_DBF_TEXT(TRACE, 3, "openREC");
		return -ERESTARTSYS;
	}
	return __qeth_l2_open(dev);
}