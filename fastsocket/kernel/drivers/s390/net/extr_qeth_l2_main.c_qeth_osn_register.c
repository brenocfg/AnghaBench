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
struct TYPE_2__ {int (* assist_cb ) (struct net_device*,void*) ;int (* data_cb ) (struct sk_buff*) ;} ;
struct qeth_card {TYPE_1__ osn_info; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 struct net_device* qeth_l2_netdev_by_devno (unsigned char*) ; 

int qeth_osn_register(unsigned char *read_dev_no, struct net_device **dev,
		  int (*assist_cb)(struct net_device *, void *),
		  int (*data_cb)(struct sk_buff *))
{
	struct qeth_card *card;

	QETH_DBF_TEXT(TRACE, 2, "osnreg");
	*dev = qeth_l2_netdev_by_devno(read_dev_no);
	if (*dev == NULL)
		return -ENODEV;
	card = (*dev)->ml_priv;
	if (!card)
		return -ENODEV;
	if ((assist_cb == NULL) || (data_cb == NULL))
		return -EINVAL;
	card->osn_info.assist_cb = assist_cb;
	card->osn_info.data_cb = data_cb;
	return 0;
}