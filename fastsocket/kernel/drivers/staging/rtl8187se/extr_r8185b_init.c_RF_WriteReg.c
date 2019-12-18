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
struct r8180_priv {int rf_chip; int RegThreeWireMode; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESGE (char*,int) ; 
#define  HW_THREE_WIRE 134 
#define  HW_THREE_WIRE_PI 133 
#define  HW_THREE_WIRE_SI 132 
 int /*<<< orphan*/  HwHSSIThreeWire (struct net_device*,int*,int,int,int) ; 
 int /*<<< orphan*/  HwThreeWire (struct net_device*,int*,int,int /*<<< orphan*/ ,int) ; 
#define  RFCHIPID_RTL8225 131 
#define  RF_ZEBRA2 130 
#define  RF_ZEBRA4 129 
#define  SW_THREE_WIRE 128 
 int /*<<< orphan*/  ZEBRA_RFSerialWrite (struct net_device*,int,int,int) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void
RF_WriteReg(
	struct net_device *dev,
	u8		offset,
	u32		data
	)
{
	//RFReg			reg;
	u32			data2Write;
	u8			len;
	u8			low2high;
	//u32			RF_Read = 0;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);


	switch(priv->rf_chip)
	{
	case RFCHIPID_RTL8225:
	case RF_ZEBRA2:		// Annie 2006-05-12.
	case RF_ZEBRA4:        //by amy
		switch(priv->RegThreeWireMode)
		{
		case SW_THREE_WIRE:
			{ // Perform SW 3-wire programming by driver.
				data2Write = (data << 4) | (u32)(offset & 0x0f);
				len = 16;
				low2high = 0;
				ZEBRA_RFSerialWrite(dev, data2Write, len, low2high);
       			}
			break;

 		case HW_THREE_WIRE:
			{ // Pure HW 3-wire.
				data2Write = (data << 4) | (u32)(offset & 0x0f);
				len = 16;
				HwThreeWire(
					dev,
					(u8 *)(&data2Write),	// pDataBuf,
					len,				// nDataBufBitCnt,
					0,					// bHold,
					1);					// bWrite
         		}
			break;
			case HW_THREE_WIRE_PI: //Parallel Interface
			{ // Pure HW 3-wire.
				data2Write = (data << 4) | (u32)(offset & 0x0f);
				len = 16;
					HwHSSIThreeWire(
						dev,
						(u8*)(&data2Write),	// pDataBuf,
						len,						// nDataBufBitCnt,
						0, 					// bSI
						1); 					// bWrite

                                //printk("33333\n");
			}
			break;

			case HW_THREE_WIRE_SI: //Serial Interface
			{ // Pure HW 3-wire.
				data2Write = (data << 4) | (u32)(offset & 0x0f);
				len = 16;
//                                printk(" enter  ZEBRA_RFSerialWrite\n ");
//                                low2high = 0;
//                                ZEBRA_RFSerialWrite(dev, data2Write, len, low2high);

				HwHSSIThreeWire(
					dev,
					(u8*)(&data2Write),	// pDataBuf,
					len,						// nDataBufBitCnt,
					1, 					// bSI
					1); 					// bWrite

//                                 printk(" exit ZEBRA_RFSerialWrite\n ");
			}
			break;


		default:
			DMESGE("RF_WriteReg(): invalid RegThreeWireMode(%d) !!!", priv->RegThreeWireMode);
			break;
		}
		break;

	default:
		DMESGE("RF_WriteReg(): unknown RFChipID: %#X", priv->rf_chip);
		break;
	}
}