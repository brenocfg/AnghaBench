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
typedef  int u32 ;
struct r8180_priv {int rf_chip; int /*<<< orphan*/  RegThreeWireMode; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  HW_THREE_WIRE_PI 132 
#define  HW_THREE_WIRE_SI 131 
 int /*<<< orphan*/  HwHSSIThreeWire (struct net_device*,int*,int,int,int /*<<< orphan*/ ) ; 
#define  RFCHIPID_RTL8225 130 
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 int /*<<< orphan*/  ZEBRA_RFSerialRead (struct net_device*,int,int,int*,int,int) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

u32
RF_ReadReg(
	struct net_device *dev,
	u8		offset
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	u32			data2Write;
	u8			wlen;
	u8			rlen;
	u8			low2high;
	u32			dataRead;

	switch(priv->rf_chip)
	{
	case RFCHIPID_RTL8225:
	case RF_ZEBRA2:
	case RF_ZEBRA4:
		switch(priv->RegThreeWireMode)
		{
			case HW_THREE_WIRE_PI: // For 87S  Parallel Interface.
			{
				data2Write = ((u32)(offset&0x0f));
				wlen=16;
				HwHSSIThreeWire(
					dev,
					(u8*)(&data2Write),	// pDataBuf,
					wlen,					// nDataBufBitCnt,
					0, 					// bSI
					0); 					// bWrite
				dataRead= data2Write;
			}
			break;

			case HW_THREE_WIRE_SI: // For 87S Serial Interface.
			{
				data2Write = ((u32)(offset&0x0f)) ;
				wlen=16;
				HwHSSIThreeWire(
					dev,
					(u8*)(&data2Write),	// pDataBuf,
					wlen,					// nDataBufBitCnt,
					1, 					// bSI
					0					// bWrite
					);
				dataRead= data2Write;
			}
			break;

			// Perform SW 3-wire programming by driver.
			default:
			{
				data2Write = ((u32)(offset&0x1f)) << 27; // For Zebra E-cut. 2005.04.11, by rcnjko.
				wlen = 6;
				rlen = 12;
				low2high = 0;
				ZEBRA_RFSerialRead(dev, data2Write, wlen,&dataRead,rlen, low2high);
			}
			break;
		}
		break;
	default:
		dataRead = 0;
		break;
	}

	return dataRead;
}