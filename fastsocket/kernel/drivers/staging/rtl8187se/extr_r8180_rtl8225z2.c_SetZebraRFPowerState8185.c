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
typedef  int u8 ;
struct r8180_priv {int SetRFPowerStateInProgress; int rf_chip; int RFProgType; int /*<<< orphan*/  eRFPowerState; int /*<<< orphan*/  txringcount; int /*<<< orphan*/  TxPollingTimes; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_RF_POWER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ANAPARAM ; 
 int /*<<< orphan*/  ANAPARAM2 ; 
 int /*<<< orphan*/  ANAPARM2_ON ; 
 int /*<<< orphan*/  ANAPARM_ON ; 
 int BIT5 ; 
 int BIT6 ; 
 int CONFIG3 ; 
 int CONFIG3_PARM_En ; 
 int CONFIG4 ; 
 int CR9346 ; 
 int /*<<< orphan*/  LPS_MAX_SLEEP_WAITING_TIMES_87SE ; 
 int MAX_DOZE_WAITING_TIMES_85B ; 
 int MAX_POLLING_24F_TIMES_87SE ; 
 int /*<<< orphan*/  RF_WriteReg (struct net_device*,int,int) ; 
#define  RF_ZEBRA2 132 
#define  RF_ZEBRA4 131 
#define  eRfOff 130 
#define  eRfOn 129 
#define  eRfSleep 128 
 int /*<<< orphan*/  get_curr_tx_free_desc (struct net_device*,int) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int read_nic_byte (struct net_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 

bool SetZebraRFPowerState8185(struct net_device *dev,
			      RT_RF_POWER_STATE eRFPowerState)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u8			btCR9346, btConfig3;
	bool bActionAllowed = true, bTurnOffBB = true;
	u8			u1bTmp;
	int			i;
	bool		bResult = true;
	u8			QueueID;

	if (priv->SetRFPowerStateInProgress == true)
		return false;

	priv->SetRFPowerStateInProgress = true;

	btCR9346 = read_nic_byte(dev, CR9346);
	write_nic_byte(dev, CR9346, (btCR9346 | 0xC0));

	btConfig3 = read_nic_byte(dev, CONFIG3);
	write_nic_byte(dev, CONFIG3, (btConfig3 | CONFIG3_PARM_En));

	switch (priv->rf_chip) {
	case RF_ZEBRA2:
		switch (eRFPowerState) {
		case eRfOn:
			RF_WriteReg(dev,0x4,0x9FF);

			write_nic_dword(dev, ANAPARAM, ANAPARM_ON);
			write_nic_dword(dev, ANAPARAM2, ANAPARM2_ON);

			write_nic_byte(dev, CONFIG4, priv->RFProgType);

			/* turn on CCK and OFDM */
			u1bTmp = read_nic_byte(dev, 0x24E);
			write_nic_byte(dev, 0x24E, (u1bTmp & (~(BIT5 | BIT6))));
			break;
		case eRfSleep:
			break;
		case eRfOff:
			break;
		default:
			bResult = false;
			break;
		}
		break;
	case RF_ZEBRA4:
		switch (eRFPowerState) {
		case eRfOn:
			write_nic_word(dev, 0x37C, 0x00EC);

			/* turn on AFE */
			write_nic_byte(dev, 0x54, 0x00);
			write_nic_byte(dev, 0x62, 0x00);

			/* turn on RF */
			RF_WriteReg(dev, 0x0, 0x009f); udelay(500);
			RF_WriteReg(dev, 0x4, 0x0972); udelay(500);

			/* turn on RF again */
			RF_WriteReg(dev, 0x0, 0x009f); udelay(500);
			RF_WriteReg(dev, 0x4, 0x0972); udelay(500);

			/* turn on BB */
			write_phy_ofdm(dev,0x10,0x40);
			write_phy_ofdm(dev,0x12,0x40);

			/* Avoid power down at init time. */
			write_nic_byte(dev, CONFIG4, priv->RFProgType);

			u1bTmp = read_nic_byte(dev, 0x24E);
			write_nic_byte(dev, 0x24E, (u1bTmp & (~(BIT5 | BIT6))));
			break;
		case eRfSleep:
			for (QueueID = 0, i = 0; QueueID < 6;) {
				if (get_curr_tx_free_desc(dev, QueueID) == priv->txringcount) {
					QueueID++;
					continue;
				} else {
					priv->TxPollingTimes ++;
					if (priv->TxPollingTimes >= LPS_MAX_SLEEP_WAITING_TIMES_87SE) {
						bActionAllowed = false;
						break;
					} else
						udelay(10);
				}
			}

			if (bActionAllowed) {
				/* turn off BB RXIQ matrix to cut off rx signal */
				write_phy_ofdm(dev, 0x10, 0x00);
				write_phy_ofdm(dev, 0x12, 0x00);

				/* turn off RF */
				RF_WriteReg(dev, 0x4, 0x0000);
				RF_WriteReg(dev, 0x0, 0x0000);

				/* turn off AFE except PLL */
				write_nic_byte(dev, 0x62, 0xff);
				write_nic_byte(dev, 0x54, 0xec);

				mdelay(1);

				{
					int i = 0;
					while (true) {
						u8 tmp24F = read_nic_byte(dev, 0x24f);

						if ((tmp24F == 0x01) || (tmp24F == 0x09)) {
							bTurnOffBB = true;
							break;
						} else {
							udelay(10);
							i++;
							priv->TxPollingTimes++;

							if (priv->TxPollingTimes >= LPS_MAX_SLEEP_WAITING_TIMES_87SE) {
								bTurnOffBB = false;
								break;
							} else
								udelay(10);
						}
					}
				}

				if (bTurnOffBB) {
					/* turn off BB */
					u1bTmp = read_nic_byte(dev, 0x24E);
					write_nic_byte(dev, 0x24E, (u1bTmp | BIT5 | BIT6));

					/* turn off AFE PLL */
					write_nic_byte(dev, 0x54, 0xFC);
					write_nic_word(dev, 0x37C, 0x00FC);
				}
			}
			break;
		case eRfOff:
			for (QueueID = 0, i = 0; QueueID < 6;) {
				if (get_curr_tx_free_desc(dev, QueueID) == priv->txringcount) {
					QueueID++;
					continue;
				} else {
					udelay(10);
					i++;
				}

				if (i >= MAX_DOZE_WAITING_TIMES_85B)
					break;
			}

			/* turn off BB RXIQ matrix to cut off rx signal */
			write_phy_ofdm(dev, 0x10, 0x00);
			write_phy_ofdm(dev, 0x12, 0x00);

			/* turn off RF */
			RF_WriteReg(dev, 0x4, 0x0000);
			RF_WriteReg(dev, 0x0, 0x0000);

			/* turn off AFE except PLL */
			write_nic_byte(dev, 0x62, 0xff);
			write_nic_byte(dev, 0x54, 0xec);

			mdelay(1);

			{
				int i = 0;

				while (true)
				{
					u8 tmp24F = read_nic_byte(dev, 0x24f);

					if ((tmp24F == 0x01) || (tmp24F == 0x09)) {
						bTurnOffBB = true;
						break;
					} else {
						bTurnOffBB = false;
						udelay(10);
						i++;
					}

					if (i > MAX_POLLING_24F_TIMES_87SE)
						break;
				}
			}

			if (bTurnOffBB) {
				/* turn off BB */
				u1bTmp = read_nic_byte(dev, 0x24E);
				write_nic_byte(dev, 0x24E, (u1bTmp | BIT5 | BIT6));

				/* turn off AFE PLL (80M) */
				write_nic_byte(dev, 0x54, 0xFC);
				write_nic_word(dev, 0x37C, 0x00FC);
			}
			break;
		default:
			bResult = false;
			printk("SetZebraRFPowerState8185(): unknow state to set: 0x%X!!!\n", eRFPowerState);
			break;
		}
		break;
	}

	btConfig3 &= ~(CONFIG3_PARM_En);
	write_nic_byte(dev, CONFIG3, btConfig3);

	btCR9346 &= ~(0xC0);
	write_nic_byte(dev, CR9346, btCR9346);

	if (bResult && bActionAllowed)
		priv->eRFPowerState = eRFPowerState;

	priv->SetRFPowerStateInProgress = false;

	return bResult && bActionAllowed;
}