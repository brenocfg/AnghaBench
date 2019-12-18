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
typedef  int u32 ;
struct TYPE_2__ {int advertising; int flowctrl; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct tg3 {int phy_flags; TYPE_1__ link_config; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int ADVERTISE_1000XFULL ; 
 int ADVERTISE_1000XHALF ; 
 int ADVERTISE_ALL ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
#define  BMCR_SPEED100 129 
#define  BMCR_SPEED1000 128 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int EIO ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  PAUSE_AUTONEG ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int TG3_PHYFLG_10_100_ONLY ; 
 int TG3_PHYFLG_ANY_SERDES ; 
 int mii_adv_to_ethtool_adv_t (int) ; 
 int mii_adv_to_ethtool_adv_x (int) ; 
 int mii_ctrl1000_to_ethtool_adv_t (int) ; 
 int tg3_decode_flowctrl_1000T (int) ; 
 int tg3_decode_flowctrl_1000X (int) ; 
 int /*<<< orphan*/  tg3_flag_clear (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tg3_phy_pull_config(struct tg3 *tp)
{
	int err;
	u32 val;

	err = tg3_readphy(tp, MII_BMCR, &val);
	if (err)
		goto done;

	if (!(val & BMCR_ANENABLE)) {
		tp->link_config.autoneg = AUTONEG_DISABLE;
		tp->link_config.advertising = 0;
		tg3_flag_clear(tp, PAUSE_AUTONEG);

		err = -EIO;

		switch (val & (BMCR_SPEED1000 | BMCR_SPEED100)) {
		case 0:
			if (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
				goto done;

			tp->link_config.speed = SPEED_10;
			break;
		case BMCR_SPEED100:
			if (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
				goto done;

			tp->link_config.speed = SPEED_100;
			break;
		case BMCR_SPEED1000:
			if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
				tp->link_config.speed = SPEED_1000;
				break;
			}
			/* Fall through */
		default:
			goto done;
		}

		if (val & BMCR_FULLDPLX)
			tp->link_config.duplex = DUPLEX_FULL;
		else
			tp->link_config.duplex = DUPLEX_HALF;

		tp->link_config.flowctrl = FLOW_CTRL_RX | FLOW_CTRL_TX;

		err = 0;
		goto done;
	}

	tp->link_config.autoneg = AUTONEG_ENABLE;
	tp->link_config.advertising = ADVERTISED_Autoneg;
	tg3_flag_set(tp, PAUSE_AUTONEG);

	if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) {
		u32 adv;

		err = tg3_readphy(tp, MII_ADVERTISE, &val);
		if (err)
			goto done;

		adv = mii_adv_to_ethtool_adv_t(val & ADVERTISE_ALL);
		tp->link_config.advertising |= adv | ADVERTISED_TP;

		tp->link_config.flowctrl = tg3_decode_flowctrl_1000T(val);
	} else {
		tp->link_config.advertising |= ADVERTISED_FIBRE;
	}

	if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
		u32 adv;

		if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) {
			err = tg3_readphy(tp, MII_CTRL1000, &val);
			if (err)
				goto done;

			adv = mii_ctrl1000_to_ethtool_adv_t(val);
		} else {
			err = tg3_readphy(tp, MII_ADVERTISE, &val);
			if (err)
				goto done;

			adv = tg3_decode_flowctrl_1000X(val);
			tp->link_config.flowctrl = adv;

			val &= (ADVERTISE_1000XHALF | ADVERTISE_1000XFULL);
			adv = mii_adv_to_ethtool_adv_x(val);
		}

		tp->link_config.advertising |= adv;
	}

done:
	return err;
}