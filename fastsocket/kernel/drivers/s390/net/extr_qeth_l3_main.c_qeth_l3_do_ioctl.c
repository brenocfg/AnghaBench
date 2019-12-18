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
struct TYPE_4__ {int /*<<< orphan*/  guestlan; int /*<<< orphan*/  type; } ;
struct qeth_card {scalar_t__ state; TYPE_2__ info; } ;
struct qeth_arp_cache_entry {int dummy; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct mii_ioctl_data {int /*<<< orphan*/  reg_num; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  val_out; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifru_data; int /*<<< orphan*/  ifru_ivalue; } ;
struct ifreq {TYPE_1__ ifr_ifru; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 scalar_t__ CARD_STATE_UP ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  QETH_CARD_TYPE_OSD ; 
 int /*<<< orphan*/  QETH_CARD_TYPE_OSX ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
#define  SIOCGMIIPHY 136 
#define  SIOCGMIIREG 135 
#define  SIOC_QETH_ADP_SET_SNMP_CONTROL 134 
#define  SIOC_QETH_ARP_ADD_ENTRY 133 
#define  SIOC_QETH_ARP_FLUSH_CACHE 132 
#define  SIOC_QETH_ARP_QUERY_INFO 131 
#define  SIOC_QETH_ARP_REMOVE_ENTRY 130 
#define  SIOC_QETH_ARP_SET_NO_ENTRIES 129 
#define  SIOC_QETH_GET_CARD_TYPE 128 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct qeth_arp_cache_entry*,int /*<<< orphan*/ ,int) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int qeth_l3_arp_add_entry (struct qeth_card*,struct qeth_arp_cache_entry*) ; 
 int qeth_l3_arp_flush_cache (struct qeth_card*) ; 
 int qeth_l3_arp_query (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_arp_remove_entry (struct qeth_card*,struct qeth_arp_cache_entry*) ; 
 int qeth_l3_arp_set_no_entries (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_mdio_read (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_snmp_command (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_do_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct qeth_card *card = dev->ml_priv;
	struct qeth_arp_cache_entry arp_entry;
	struct mii_ioctl_data *mii_data;
	int rc = 0;

	if (!card)
		return -ENODEV;

	if ((card->state != CARD_STATE_UP) &&
		(card->state != CARD_STATE_SOFTSETUP))
		return -ENODEV;

	switch (cmd) {
	case SIOC_QETH_ARP_SET_NO_ENTRIES:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		rc = qeth_l3_arp_set_no_entries(card, rq->ifr_ifru.ifru_ivalue);
		break;
	case SIOC_QETH_ARP_QUERY_INFO:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		rc = qeth_l3_arp_query(card, rq->ifr_ifru.ifru_data);
		break;
	case SIOC_QETH_ARP_ADD_ENTRY:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		if (copy_from_user(&arp_entry, rq->ifr_ifru.ifru_data,
				   sizeof(struct qeth_arp_cache_entry)))
			rc = -EFAULT;
		else
			rc = qeth_l3_arp_add_entry(card, &arp_entry);
		break;
	case SIOC_QETH_ARP_REMOVE_ENTRY:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		if (copy_from_user(&arp_entry, rq->ifr_ifru.ifru_data,
				   sizeof(struct qeth_arp_cache_entry)))
			rc = -EFAULT;
		else
			rc = qeth_l3_arp_remove_entry(card, &arp_entry);
		break;
	case SIOC_QETH_ARP_FLUSH_CACHE:
		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		rc = qeth_l3_arp_flush_cache(card);
		break;
	case SIOC_QETH_ADP_SET_SNMP_CONTROL:
		rc = qeth_snmp_command(card, rq->ifr_ifru.ifru_data);
		break;
	case SIOC_QETH_GET_CARD_TYPE:
		if ((card->info.type == QETH_CARD_TYPE_OSD ||
		     card->info.type == QETH_CARD_TYPE_OSX) &&
		    !card->info.guestlan)
			return 1;
		return 0;
		break;
	case SIOCGMIIPHY:
		mii_data = if_mii(rq);
		mii_data->phy_id = 0;
		break;
	case SIOCGMIIREG:
		mii_data = if_mii(rq);
		if (mii_data->phy_id != 0)
			rc = -EINVAL;
		else
			mii_data->val_out = qeth_mdio_read(dev,
							mii_data->phy_id,
							mii_data->reg_num);
		break;
	default:
		rc = -EOPNOTSUPP;
	}
	if (rc)
		QETH_DBF_TEXT_(TRACE, 2, "ioce%d", rc);
	return rc;
}